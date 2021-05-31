# diffmatrix
Compare two discrete character matrices stored in Nexus files and print out the differences.

This program uses the [NCL by Mark Holder](https://github.com/mtholder/ncl).

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

The output of the program is pretty basic. If any differences are found in a particular character, the taxon name will be printed with an output of the scoring 
from file1.nex (left column) and file2.nex (right column)

### Example output:
```
Character 30
          Galeaspida	0123   01

Character 31
          Gemuendina	01   1
            Jagorina	01   1

Character 59
         Kansasiella	1   ?
            Achoania	0   ?

Character 80
   Macropetalichthys	0   ?

Character 88
         Cladodoides	?   1
    Parayunnanolepis	0   ?
           Romundina	0   ?
```
