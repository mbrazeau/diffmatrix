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

*NOTE:* Diffmatrix is new and written in an afternoon. It should not be used on matrices with different dimensions or with different taxon/character ordering.
This will be improved in a future release. For now, it basically lets you compare your updates to a matrix of fixed size.

## Output


## Building diffmatrix from source
You should have a C++ compiler on your machine. To use the convenience utilities and build systems, you should also have python, git, and CMAKE installed.

### Building with the build scripts

### Building `manually`

