#!/bin/bash

set -e

conan install . --output-folder=conan/install-Debug --build=missing -s build_type=Debug
conan install . --output-folder=conan/install-Release --build=missing -s build_type=Release
