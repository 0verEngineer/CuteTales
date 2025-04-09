#!/bin/bash

set -x
set -e

# run_tests_and_generate_coverage needs the test type as parameter, aka unit or integration exactly like the directory names
function run_tests_and_generate_coverage() {
  local testType=$1

  # Run the tests of the given type
  set +e
  ctest -C $CURRENT_BUILD_TYPE --test-dir $CI_PROJECT_DIR/build/src/test/$testType --output-junit $OUT_DIR/test-results-$testType.xml
  set -e

  # Capture the coverage data
  lcov -c -d $CI_PROJECT_DIR/build -o $CI_PROJECT_DIR/build/coverage-$testType.info --rc lcov_branch_coverage=1

  # Combine the base and testing coverage data
  lcov -a $CI_PROJECT_DIR/build/coverage-base.info -a $CI_PROJECT_DIR/build/coverage-$testType.info -o $CI_PROJECT_DIR/build/coverage_unfiltered-$testType.info --rc lcov_branch_coverage=1

  # Filter out test code, system headers and other unwanted stuff
  lcov --ignore-errors unused --remove $CI_PROJECT_DIR/build/coverage_unfiltered-$testType.info -o $CI_PROJECT_DIR/build/coverage-$testType.info --rc lcov_branch_coverage=1 \
    '*/test/*' \
    '*/usr/*' \
    '*_autogen/*' \
    '*/Qt/6.*' \
    '*/CuteTales/build/*' \
    '*executable/main.cpp'

  # Generate HTML report
  genhtml $CI_PROJECT_DIR/build/coverage-$testType.info --output-directory $OUT_DIR/coverage-$testType-html --rc genhtml_branch_coverage=1
}


mkdir -p outLinux
export OUT_DIR="$CI_PROJECT_DIR/outLinux"
export CURRENT_BUILD_TYPE="Release"

# Set the conan home variable for caching, DO NOT CHANGE NAME without changing the gitlab-runner config
export CONAN_HOME="/conanHomes/CuteTales"

# Add test coverage flags
if [ "$RUN_TESTS" == "ON" ]; then
  export QT_QPA_PLATFORM=offscreen
  export CMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS --coverage"
  export CURRENT_BUILD_TYPE="Debug"
  echo "RUN_TESTS is ON, set CURRENT_BUILD_TYPE to 'Debug' and modified CMAKE_CXX_FLAGS: $CMAKE_CXX_FLAGS"
fi

# Dependencies
conan install . --output-folder=conan/install-$CURRENT_BUILD_TYPE --build=missing -s build_type=$CURRENT_BUILD_TYPE --profile:host=conan/profiles/linux-x86_64-AppImage --profile:build=conan/profiles/linux-x86_64-AppImage

# Configure
qt-cmake . -G Ninja -B ./build \
  -DCMAKE_BUILD_TYPE=$CURRENT_BUILD_TYPE \
  -DCMAKE_GENERATOR=Ninja \
  -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS"

# Build
cmake --build ./build --target all

# Run Tests
if [ "$RUN_TESTS" == "ON" ]; then
  # Do a capture before executing the tests to create a zero coverage file: https://stackoverflow.com/questions/44203156/can-lcov-genhtml-show-files-that-were-never-executed
  lcov -c -i -d $CI_PROJECT_DIR/build -o $CI_PROJECT_DIR/build/coverage-base.info --rc lcov_branch_coverage=1
  
  run_tests_and_generate_coverage unit
  run_tests_and_generate_coverage integration

  # Combine the unit and integration coverage data
  lcov -a $CI_PROJECT_DIR/build/coverage-unit.info -a $CI_PROJECT_DIR/build/coverage-integration.info -o $CI_PROJECT_DIR/build/coverage.info --rc lcov_branch_coverage=1

  # lcov to cobertura
  lcov_cobertura $CI_PROJECT_DIR/build/coverage.info --output=$OUT_DIR/coverage.xml

  python3 $CI_PROJECT_DIR/ci/scripts/print_coverage.py $OUT_DIR/coverage.xml

  # Generate HTML report for all test types
  genhtml $CI_PROJECT_DIR/build/coverage.info --output-directory $OUT_DIR/coverage-html --rc genhtml_branch_coverage=1

  # Merge the junit xml outputs
  junitparser merge $OUT_DIR/test-results-unit.xml $OUT_DIR/test-results-integration.xml $OUT_DIR/test-results.xml
fi
