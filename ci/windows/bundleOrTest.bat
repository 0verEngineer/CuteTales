echo on

setlocal enabledelayedexpansion

set "lastUnitTestExeFullPath="

:: Setup VS env
call "%VS_DIR%\VC\Auxiliary\Build\vcvars64.bat"

:: Setup our env
mkdir outWin
set "OUT_DIR=%CI_PROJECT_DIR%\outWin"

:: Flags
set "CURRENT_BUILD_TYPE=Release"

if "%RUN_TESTS%"=="ON" (
    set "CURRENT_BUILD_TYPE=Debug"
    echo "RUN_TESTS is ON, set CURRENT_BUILD_TYPE to 'Debug'"
)

:: Install dependencies
conan install . --output-folder=conan/install-%CURRENT_BUILD_TYPE% --build=missing -s build_type=%CURRENT_BUILD_TYPE% ^
    --profile:build=conan/profiles/windows_vs ^
    --profile:host=conan/profiles/windows_vs

:: Configure
C:/Qt/Tools/CMake_64/bin/cmake.exe -S . -B ./build ^
    "-DCMAKE_GENERATOR:STRING=Ninja" "-DCMAKE_BUILD_TYPE:STRING=%CURRENT_BUILD_TYPE%" ^
    "-DCMAKE_PREFIX_PATH:PATH=%QT_DIR%/msvc2019_64" "-DCMAKE_C_COMPILER:FILEPATH=cl.exe" "-DCMAKE_CXX_COMPILER:FILEPATH=cl.exe"

:: Build
C:/Qt/Tools/CMake_64/bin/cmake.exe --build ./build --target all

echo "RUN_TESTS: %RUN_TESTS%"

if "%RUN_TESTS%"=="ON" (
    call :run_tests_and_generate_coverage unit
    call :run_tests_and_generate_coverage integration

    echo "lastUnitTestExeFullPath: !lastUnitTestExeFullPath!"

    :: Merge coverage reports, create cobertura and html
    OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=cobertura:%OUT_DIR%\coverage.xml --no_aggregate_by_file ^
        --input_coverage=%CI_PROJECT_DIR%\build\coverage-unit.coverage --input_coverage=%CI_PROJECT_DIR%\build\coverage-integration.coverage

    OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=html:%OUT_DIR%\CoverageReport --no_aggregate_by_file ^
        --input_coverage=%CI_PROJECT_DIR%\build\coverage-unit.coverage --input_coverage=%CI_PROJECT_DIR%\build\coverage-integration.coverage

    python %CI_PROJECT_DIR%/ci/scripts/print_coverage.py %OUT_DIR%\coverage.xml

    :: Merge the junit xml outputs
    junitparser merge %OUT_DIR%\test-results-unit.xml %OUT_DIR%\test-results-integration.xml %OUT_DIR%\test-results.xml
) else (
    :: Bundle
    mkdir outWin
    mkdir outWin\CuteTales
    move .\build\src\executable\*.exe .\outWin\CuteTales\
    move .\build\src\executable\*.dll .\outWin\CuteTales\
    move .\build\*.qm .\outWin\CuteTales\
    %QT_DIR%/msvc2019_64/bin/windeployqt.exe --qmldir . --dir ./outWin/CuteTales --libdir ./outWin/CuteTales --plugindir ./outWin/CuteTales ./outWin/CuteTales/CuteTales.exe
)

goto :eof  :: Jump to end of file before reaching the function


:run_tests_and_generate_coverage
    echo "run_tests_and_generate_coverage called with %1"
    set "testType=%1"

    set "typeValid=false"
    if "!testType!"=="unit" (
        set "typeValid=true"
    )
    if "!testType!"=="integration" (
        set "typeValid=true"
    )

    if "!typeValid!"=="false" (
        echo "Invalid testType: !testType!"
        exit /b
    )

    echo "## Running tests for !testType! ##"

   :: Run Tests, if OpenCppCoverage could output a test-results.xml as well we would not need this and the tests would
   ::  only be run once instead of twice
   ctest -C %CURRENT_BUILD_TYPE% --test-dir %CI_PROJECT_DIR%/build/src/test/!testType! --output-junit %OUT_DIR%/test-results-!testType!.xml
   set "inputCoverageAppendix="
   set "lastTestExeFullPath="

    set "loop_path=!CI_PROJECT_DIR!/build/src/test/!testType!"
    cd !loop_path!
    echo "loop_path: !loop_path!"
    for /R ".\" %%F in (*Test.exe) do (
       echo "Running coverage for %%F with inputCoverageAppendix: !inputCoverageAppendix!"
       OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=binary:%%F.coverage --no_aggregate_by_file !inputCoverageAppendix! -- "%%F"
       set "lastTestExeFullPath=%%F"
       set "inputCoverageAppendix=--input_coverage=%%F.coverage"

       echo "inputCoverageAppendix after run: !inputCoverageAppendix!"

       if "!testType!"=="unit" (
           set "lastUnitTestExeFullPath=%%F"
       )
    )

   :: Merge coverage reports, create cobertura and html for the last coverage report of the last test executable
   OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=cobertura:%OUT_DIR%\coverage-!testType!.xml --no_aggregate_by_file !inputCoverageAppendix!
   OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=html:%OUT_DIR%\CoverageReport-!testType! --no_aggregate_by_file !inputCoverageAppendix!
   :: Also create binary merged reports, for the merging of the complete report
   OpenCppCoverage.exe --sources %CI_PROJECT_DIR%\src\app --export_type=binary:%CI_PROJECT_DIR%\build\coverage-!testType!.coverage --no_aggregate_by_file !inputCoverageAppendix!

   cd %CI_PROJECT_DIR%

exit /b

endlocal
