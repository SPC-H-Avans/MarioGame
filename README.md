# Platformer Game

[![CPP Clang Tidy Linter](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/clang.yml/badge.svg)](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/clang.yml)
[![Build](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/build.yml/badge.svg)](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/build.yml)
[![Publish](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/publish.yml/badge.svg)](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/publish.yml)
[![Doxygen](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/doxygen.yml/badge.svg)](https://github.com/SPC-H-Avans/MarioGame/actions/workflows/doxygen.yml)

# Getting Started
- Install [VCPKG](https://vcpkg.io/en/index.html)
- Clone the repository
- Follow MacOS instructions if you are on MacOS, if you are on Windows follow the Windows instructions, otherwise continue
- Run `vcpkg integrate install`
- Run `git submodule update --init --recursive`
- Add the following CMake options:
    - `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`
    - `-DVCPKG_TARGET_TRIPLET=[x64-windows | x64-osx | arm64-osx | x64-linux ]` (depending on your platform)
    - When using CLion, go to `File (Preferences on MacOS) > Settings > Build, Execution, Deployment > CMake > CMake Options` and add the options there

## MacOS
- Install [Brew](https://docs.brew.sh/Installation)
- Install CMake: `brew install cmake`
- Install GCC: `brew install gcc`
- Install VCPKG to the terminal:
  - `./vcpkg integrate bash`
  - `./vcpkg integrate zsh`
- Continue with the instructions above

## Windows
- Add the VCPKG directory to your PATH environment variable
- Continue with the instructions above

# Contributing
- Create a new branch
- Make your changes
- Update the CHANGELOG.md file
- Create a pull request and assign it to two team members. The GitHub Actions must succeed and both team members must approve the pull request before it can be merged.

# Making a pull request
- Make sure you have updated the CHANGELOG.md file
- Make sure you have added the Jira ticket number to the title
- Fill out the pull request template
- Assign two team members to review your pull request
- The GitHub Actions must succeed and both team members must approve the pull request before it can be merged.

# How to create a new release
- Merge the develop branch into the main branch
- Create a new tag on the main branch, use the following naming tema: `v[Major].[Minor].[Patch]`
- The GitHub Actions will automatically create a new release and publish it to the [game-builds](https://github.com/SPC-H-Avans/game-builds/releases) repository

# Documentation
- [Doxygen](https://game.mrproper.dev)
