# project robotrun software

- [robot product page](https://www.pololu.com/product/975/resources)
- [wixel product page](https://www.pololu.com/product/1336/resources)

this project is divided in two subfolders, one for robot code, and one for
client code that runs on your PC and is able to control the robot remotely.

## supported features

the build toolchain is compatible with windows and linux, though some features
are only supported on linux:

|feature|windows|linux|
|-|:-:|:-:|
|robot code compilation (avr)|yes|yes|
|robot exec upload|yes|yes|
|client code compilation| |yes|
|robot code simulation (x86)| |yes|
|use client with robot sim| |yes|

the client only compiles and runs on linux due to time constraints. because
package names vary from distribution to distribution, no scripts are included
to install the necessary build tools for linux.

## toolchain installation on windows

> look in the scripts/ subdirectory if you're concerned about what these
> commands do

1. open a regular powershell window (no administrator!)
2. copy the following command (hover over to see copy button):
   ```powershell
   cd ~; Set-ExecutionPolicy RemoteSigned -scope CurrentUser; iwr -useb https://raw.githubusercontent.com/lonkaars/wall-e2/master/scripts/bootstrap.ps1 | iex
   ```
3. paste the command by right-clicking or pressing
   <kbd>shift</kbd>+<kbd>insert</kbd> **ctrl+v doesn't work in the powershell
   window**
4. press <kbd>enter</kbd>, then <kbd>y</kbd>, then <kbd>enter</kbd> again.
5. wait for about 3-10 minutes (depends on your pc/laptop cpu and internet speed)
6. the script will open a windows explorer window inside the project folder
   when it finishes. the powershell window can be closed when it's done.

now you're ready to edit this project! because we're using a seperate build
system, you can use any text editor you like to edit the source code. i
recommend [visual studio code](https://code.visualstudio.com) if you don't have
a preferred text editor.

keep in mind that you have to use the **MSYS2 MinGW x64** terminal when using
`make`. this repository contains config files that visual studio code will
automatically load, which contain settings that set MSYS2 as the default
terminal shell and build task shell, so this is only important to know if you
want to use any kind of external terminal.

## map

[link to the map design file (figma)](https://www.figma.com/file/fPlfOqtEvQYVA9TYWNjz1i/kaart)

the map uses the following dimensions:

- a0 paper size
- 3/4" (~19mm) line width
- curved lines may not have a corner radius tighter than 3" (~75mm)
- the charging station is a black dot with a diameter of 3" (~75mm)
- page margin and minimum line margin of 3" (~75mm)
- (in grid) tile size of 8" (~20cm)
- 'crosswalk' has 2 dashes with a length of 3/8" (~10mm)
- 'crosswalk' dashes have a margin of 3/8" (~10mm)

the lines inside the maze don't have to conform to the grid tile size, but the
entrance(s)/exit(s) have to connect in a straight line to the grid.

