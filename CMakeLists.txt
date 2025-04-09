cmake_minimum_required(VERSION 3.30)

# Conan setup
if (FLATPAK_BUILD)
else ()
    set(TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/conan/install-${CMAKE_BUILD_TYPE}/conan_toolchain.cmake")
    message(Setting " CMAKE_TOOLCHAIN_FILE to: ${TOOLCHAIN_FILE}")
    set(CMAKE_TOOLCHAIN_FILE ${TOOLCHAIN_FILE})
    # Disable conan setup in QtCreator for now as long as it is not tested
    set(QT_CREATOR_SKIP_CONAN_SETUP ON)
endif()

set(PROJECT_NAME CuteTales)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

## Dependencies ##
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools Concurrent)

## Language files ##
set(TS_FILES
        ${PROJECT_SOURCE_DIR}/languages/CuteTales_de_DE.ts
)

## General assets ##
set(PROJECT_ASSETS
        ${PROJECT_SOURCE_DIR}/assets/licenses.qrc
# Todo: theming
#        ${PROJECT_SOURCE_DIR}/assets/themes/breeze/breeze.qrc
#        ${PROJECT_SOURCE_DIR}/assets/themes/system/systemStyleSheet.qrc
)

enable_testing(true)

add_subdirectory(src)