# scripts

this directory contains scripts for installing necessary build tools for
compiling and uploading code to the robot/client.

|file|description|
|-|-|
|`bootstrap.ps1`|download msys2 installer, install msys2, download and run `install-mingw-packages.sh`, clone the repository using git, run `install-sdk.sh`, start windows explorer in the project folder.|
|`install-mingw-packages.sh`|install required packages (`make`, `git`, `avr-gcc-toolchain`, `python3`, `pip3`, `avrdude`, `clangd`, `clang-tidy`, `clang-format`)|
|`install-sdk.sh`|install pololu c/c++ sdk, install wixel command-line tools (if on linux), install `compiledb` using `pip3`|
|`patch-may-26.sh`|patch|

i'm aware the powershell script is ugly, i don't like windows

