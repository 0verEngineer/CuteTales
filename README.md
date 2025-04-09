

# Development Setup
## Infos
### Used Compiler
#### Windows
- MSVC
#### Linux
- GCC
#### MacOS
- Clang

## Dependencies
### External
- Qt (required >= 6.8)
### Conan
none at the moment

## Install dependencies
1. Setup conan profile if not existent:
   conan profile detect
2. Make sure msvc is used on windows
3. Setup for Ide usage:
    - Windows: `.\conan\install.bat`
    - Unix like: `./conan/install.sh`

## IDE Setup
### CLion
1. After opening the Project a configutation dialog should pup up (Settings -> Build, Execution, Deployment -> CMake) asking to configure the project
2. A Debug Profile should be auto generated, add `-DCMAKE_PREFIX_PATH=<path-to-qt>` to CMake options
3. Add another Profile (Release) and add the CMake options here too
4. I also like to use the CMake auto reload feature (Checkbox at the top)
5. (Windows): Make sure the Visual Studio Toolchain is used, if not it can be changed in (Settings -> Build, Execution, Deployment -> Toolchains)
6. You should now be able to build the project

#### Visual Studio
1. An example `CMakeSettings.json` file is in the repository, edit the paths if needed
2. Open the project with the `Open a local folder` option

#### Visual Studio Code
1. Make sure you have the C/C++ Extension Pack and the CMake Tools Extension installed
2. Open the Project and wait for the kit selection to pop up at the top of the window
3. Choose the Visual Studio AMD64 kit on Windows; Todo: Linux and MacOS
4. Sometimes (because VSCode) the environment in the terminal is not correctly set from the `.vscode/settings.json` file, if this happens add the qt binary dir to your systems user path


# Development Infos

## Used Tools
### Tools
- Conan2 as package manager

## Translation Lupdate command
- lupdate <project path> -ts <translation file path>

## CI / CD / Builds
- At the moment it runs on my private GitLab, this will be migrated in the future.
  - I just push the code to two origins at the moment
- The Codeberg mirror job already runs on GitHub

## Todos
- Move Pipeline / CI to GitHub
- Replace the generated icon


# Special Thanks
## Qt
- Licensed under LGPL v3
- http://www.qt-project.org/legal
## Breeze Icons
- Licensed under LGPL v3
- https://github.com/KDE/breeze-icons
## BreezeDark stylesheet
- Licensed under the MIT License
- https://github.com/Alexhuszagh/BreezeStyleSheets
