# diffmatrix
Compare two discrete character matrices stored in Nexus files and print out the differences.

This program uses the [NCL by Mark Holder](https://github.com/mtholder/ncl). See instructions on building from source below for details on obtaining this dependency.

## Download and install
For the most part, no installation is necessary but some systems may require bypassing security restrictions on your system. You should be familiar with your system's command console/terminal program.

### macOS
[Download for Mac (Apple Silicon: M1)](https://github.com/mbrazeau/diffmatrix/releases/download/v2.0/diffmatrix_macOS_M1)

This is compatible with new macs running M1 chips (Apple Silicon only). Please contact me if you need a build for an Intel processor.

After downloading, you will need to open Terminal (in the Applications/Utilities folder), navigate to where the diffmatrix download sits, and use the command

`chmod a+x diffmatrix_macOS_M1`

Then attempt to run the program with the useage below. This will fail.

Open System Settings > Privacy & Security, scroll down to Security. There should be a field asking you if you want to run diffmatrix anyway. Click affirmatively.

### Windows
[Download for Windows](https://github.com/mbrazeau/diffmatrix/releases/download/v2.0/diffmatrix_Winx86.exe)

This should work as-is, but Windows may throw a warning. Click "More info" and then allow the program to run anyway.

## Usage

The program requires two valid Nexus files and delivers best results if the character and state labels are fully defined for all characters in the matrix. Place the two Nexus files in the same directory as the diffmatrix executable and enter the program name followed by the name of each file being compared:

```
./diffmatrix file1.nex file2.nex
```

To redirect the output to a text file:
```
./diffmatrix file1.nex file2.nex > output.txt
```

### Windows:
Windows useage is fundamentally the same, however instead of `./diffmatrix`, the user issues uses `diffmatrix.exe`. Redirecting the output to a file is probably best as copy-pasting from the command console often does not work.

## Output
The program will output three main blocks to the terminal or to the output file:

1. Comparison of changes to the taxon list
2. Comparison of changes to the character list
3. A log of score changes. A CSV-formatted output of all the score changes (currently minus changes to polymorphisms).

The CSV list can be copied into a plain text file by copy pasting from the buffer. This can be opened in any spreadsheet editor and formatted into a tidy changelog for your paper.

## Building diffmatrix from source
You should have a C++ compiler on your machine. To use the convenience utilities and build systems, you should also have python, git, and CMAKE installed.

### Building with the build scripts
The easiest way to build the program is to ensure that you have installed python, git, and CMake on your system. In your terminal, run the `getdeps.py` script with the following command:

```python getdeps.py build```

This should clone everything needed and will run CMake to build the executable

### Building manually

