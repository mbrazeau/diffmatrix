# diffmatrix
Compare two discrete character matrices stored in Nexus files and print out the differences.

This program uses the [NCL by Mark Holder](https://github.com/mtholder/ncl). See instructions on building from source below for details on obtaining this dependency.

## Download and install
For the most part, no installation is necessary but some systems may require bypassing security restrictions on your system. You should be familiar with your system's command console/terminal program.

### macOS
[Download for Mac (Apple Silicon: M1)](https://github.com/mbrazeau/diffmatrix/releases/download/v2.0/diffmatrix_macOS_M1)

This is compatible with new macs running M1 chips (Apple Silicon only) and is **tested on macOS Ventura 13.4.1**. Please contact me if you need a build for an Intel processor.

After downloading, you will need to open Terminal (in the Applications/Utilities folder), navigate to where the diffmatrix download sits, and use the command

`chmod a+x diffmatrix_macOS_M1`

Then attempt to run the program with the useage below. This will fail.

Open System Settings > Privacy & Security, scroll down to Security. There should be a field asking you if you want to run diffmatrix anyway. Click affirmatively.

### Windows
[Download for Windows](https://github.com/mbrazeau/diffmatrix/releases/download/v2.0/diffmatrix_Winx86.exe)

This is compatible with any Windows 10 systems. It should work as-is, but Windows may throw a warning. Click "More info" and then allow the program to run anyway.

## Using diffmatrix

Diffmatrix is a simple console utility. This means you should have a basic understanding of using your system's command prompt (e.g. Terminal or, on Windows, `cmd.exe`). 
Diffmatrix is not an interactive program. 
If there are no inputs, the program will display a welcome screen explaining the useage and then terminate.


The program requires two valid Nexus files and **gives best results if the character and state labels are fully defined for all characters in the data files**. 


1. Place the two Nexus files in the same directory (folder) as the `diffmatrix` executable.
2. Open your system's console (`Terminal` or `cmd.exe`) program.
3. To simplify matters, set the current directory to the place where you have diffmatrix and your data files. On most systems, this uses the `cd` command. For instance, if I have put all the relevant files into a folder on my system called `mynexusproject` then setting the working directory there would use the command:

```
  cd /Users/mbrazeau/mynexusproject
```

or on Windows, it might be something like:

```
  cd C:\Users\mbrazeau\mynexusproject
```

The exact path will differ on your system. 
**Note:** You don't need to type out your whole file path manually.
Most systems have shortcuts for this.
The easiest way to get the path is simply enter `cd` followed by a space, then drag and drop the folder from the file browser into the console. 
Your system will automatically fill in the path for you.
Your file browser should also have the option for you to copy a file path as text which you can paste into your console.


4. Finally, enter the program name followed by the name of each file being compared (see below for slightly different useage on Windows):

```
./diffmatrix file1.nex file2.nex
```

### Windows:
Windows useage is fundamentally the same, however instead of `./diffmatrix`, the user issues uses `diffmatrix.exe`. Redirecting the output to a file is probably best as copy-pasting from the command console often does not work.


## Output
The program should run in a few seconds. It will output three main blocks to the terminal or to the output file:

1. Comparison of changes to the taxon list
2. Comparison of changes to the character list
3. A log of score changes. A CSV-formatted output of all the score changes (currently minus changes to polymorphisms).

The CSV list can be copied into a plain text file by copy pasting from the buffer. This can be opened in any spreadsheet editor and formatted into a tidy changelog for your paper.


To redirect the output to a text file:
```
./diffmatrix file1.nex file2.nex > output.txt
```

## Building diffmatrix from source
If you would like to build diffmatrix from source, you should have a C++ compiler on your machine. To use the convenience utilities and build systems, you should also have python, git, and CMAKE installed. 

### Building with the build scripts
The easiest way to build the program is to ensure that you have installed python, git, and CMake on your system. In your terminal, run the `getdeps.py` script with the following command:

```python getdeps.py build```

This should clone everything needed and will run CMake to build the executable

### Building manually

