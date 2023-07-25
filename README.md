# diffmatrix
Compare two discrete character matrices stored in Nexus files and print out the differences.

This program uses the [NCL by Mark Holder](https://github.com/mtholder/ncl). See instructions on building from source below for details on obtaining this dependency.

## Usage
```
./diffmatrix file1.nex file2.nex
```

To redirect the output to a text file:
```
./diffmatrix file1.nex file2.nex > output.txt
```


## Output
The program will output three main blocks:

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

