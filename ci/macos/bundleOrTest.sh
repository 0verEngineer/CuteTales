#!/bin/bash

set -x
set -e

# run_tests_and_generate_coverage needs the test type as parameter, aka unit or integration exactly like the directory names
function run_tests_and_generate_coverage() {
  local testType=$1

  set +e
  ctest -C $CURRENT_BUILD_TYPE --test-dir $CI_PROJECT_DIR/build/src/test/$testType --output-junit $OUT_DIR/test-results-$testType.xml
  set -e

  llvm-profdata merge -sparse $CI_PROJECT_DIR/build/src/test/$testType/default.profraw -o $CI_PROJECT_DIR/build/merged-coverage-$testType.profdata
  
  # Profdata to lcov
  find $CI_PROJECT_DIR/build/src/app/CMakeFiles/app.dir/ -name "*.o" -print0 | \
    xargs -0 -I {} llvm-cov export -format=lcov -instr-profile=$CI_PROJECT_DIR/build/merged-coverage-$testType.profdata {} \
    > $CI_PROJECT_DIR/build/coverage-unfiltered-$testType.info

  # Filter out test code, system headers and other unwanted stuff
  lcov --ignore-errors unused --remove $CI_PROJECT_DIR/build/coverage-unfiltered-$testType.info -o $CI_PROJECT_DIR/build/coverage-$testType.info \
    '*/test/*' \
    '*_autogen/*' \
    '*/Qt/6.*'
    
  genhtml $CI_PROJECT_DIR/build/coverage-$testType.info --output-directory $OUT_DIR/coverage-$testType-html
}


# Sourcing of environment variables exported in bash_profile does not work in bash on MacOS for me..
export QT_BASE_DIR="/Library/Qt/"
export QT_DIR="${QT_BASE_DIR}/6.8.0"

export QT_QPA_PLATFORM=offscreen

mkdir -p outMac/mac-arm-to-x86_64
mkdir -p outMac/mac-arm
export OUT_DIR="$CI_PROJECT_DIR/outMac"
export CURRENT_BUILD_TYPE="Release"

# Add test coverage flags
if [ "$RUN_TESTS" == "ON" ]; then
  export CMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS -fprofile-instr-generate -fcoverage-mapping"
  export CMAKE_EXE_LINKER_FLAGS="$CMAKE_EXE_LINKER_FLAGS -fprofile-instr-generate"
  CURRENT_BUILD_TYPE="Debug"
  echo "RUN_TESTS is ON, set CURRENT_BUILD_TYPE to 'Debug' and modified CMAKE_CXX_FLAGS: $CMAKE_CXX_FLAGS"
fi


# Dependencies
conanInstall="conan install . --output-folder=conan/install-$CURRENT_BUILD_TYPE --build=missing -s build_type=$CURRENT_BUILD_TYPE"
if [ "$CMAKE_OSX_ARCHITECTURES" == "x86_64" ]; then
  OUT_DIR+="/mac-arm-to-x86_64"
  conanInstall+=" --profile:host=conan/profiles/mac-arm-to-mac-x86_64 --profile:build=conan/profiles/mac-arm"
else
  OUT_DIR+="/mac-arm"
  conanInstall+=" --profile:build=conan/profiles/mac-arm --profile:host=conan/profiles/mac-arm"
fi

eval $conanInstall


# Configure
$QT_BASE_DIR/Tools/CMake/CMake.app/Contents/bin/cmake -S ./ -B $CI_PROJECT_DIR/build \
  -DCMAKE_BUILD_TYPE:STRING=$CURRENT_BUILD_TYPE \
  -DCMAKE_PREFIX_PATH:PATH=$QT_DIR/macos \
  -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
  -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
  -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" \
  -DCMAKE_EXE_LINKER_FLAGS="$CMAKE_EXE_LINKER_FLAGS"

# Build
$QT_BASE_DIR/Tools/CMake/CMake.app/Contents/bin/cmake --build $CI_PROJECT_DIR/build --target all


# Run Tests
if [ "$RUN_TESTS" == "ON" ]; then
  run_tests_and_generate_coverage unit
  run_tests_and_generate_coverage integration

  # Combine the unit and integration coverage data
  lcov -a $CI_PROJECT_DIR/build/coverage-unit.info -a $CI_PROJECT_DIR/build/coverage-integration.info -o $CI_PROJECT_DIR/build/coverage.info

  # lcov to cobertura
  lcov_cobertura $CI_PROJECT_DIR/build/coverage.info --output=$OUT_DIR/coverage.xml

  python3 $CI_PROJECT_DIR/ci/scripts/print_coverage.py $OUT_DIR/coverage.xml

  # Generate HTML report for all test types
  genhtml $CI_PROJECT_DIR/build/coverage.info --output-directory $OUT_DIR/coverage-html --rc genhtml_branch_coverage=1

  # Merge the junit xml outputs
  junitparser merge $OUT_DIR/test-results-unit.xml $OUT_DIR/test-results-integration.xml $OUT_DIR/test-results.xml

else # Non-Testing
 # Package
 $QT_DIR/macos/bin/macdeployqt $CI_PROJECT_DIR/build/src/executable/CuteTales.app -verbose=1 -dmg -appstore-compliant
 mv $CI_PROJECT_DIR/build/src/executable/*.app $OUT_DIR
fi
