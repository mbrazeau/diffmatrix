//
//  main.cpp
//  diffmatrix
//
//  Created by Martin Brazeau on 28/05/2021.
//

#include <iostream>
#include <iomanip>
#include <vector>

#include <stdlib.h>

#include "ncl.h"

bool compare_cells(NxsCharactersBlock &cb1, NxsCharactersBlock &cb2, unsigned i, unsigned j)
{
    int nstates1 = cb1.GetNumStates(i, j);
    int nstates2 = cb2.GetNumStates(i, j);
    
    if (nstates1 != nstates2) {
        return false;
    }
    
    int s;
    for (s = 0; s < nstates1; ++s) {
        if (cb1.GetInternalRepresentation(i, j, s) != cb1.GetInternalRepresentation(i, j, s)) {
            return false;
        }
    }
    
    return true;
}

void find_differences(MultiFormatReader &f1reader, MultiFormatReader &f2reader)
{
    std::vector<unsigned int> diffs;
    
    int ntax1 = f1reader.GetTaxaBlock(0)->GetNTax();
    int nchar1 = f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetNCharTotal();
    
    int ntax2 = f2reader.GetTaxaBlock(0)->GetNTax();
    int nchar2 = f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetNCharTotal();
    
    if ((ntax1 != ntax2) || (nchar1 != nchar2)) {
        std::cout << "Warning: matrices have different dimensions" << std::endl; // TODO: Give specifics. Ask to proceed.
    }
    
    unsigned int c;
    unsigned int t;
    
    for (c = 0; c < nchar1; ++c) {
        std::cout << "Character " << c + 1 << std::endl;
        
        for (t = 0; t < ntax1; ++t) {
            // Get the character output
            
            if (compare_cells(*f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0),
                              *f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)
                              , t, c) == false)
            {
                std::cout << std::setw(20);
                std::cout << f1reader.GetTaxaBlock(0)->GetTaxonLabel(t);
                std::cout << "\t";
                int i = 0;
     
                if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i) < 0) {
                    if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i) == -3) {
                        std::cout << "-";
                    } else {
                        std::cout << "?";
                    }
                }
                else {
        //            std::cout << "\t";
                    for (i = 0; i < f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetNumStates(t, c); ++i) {
                        std::cout << f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i);
                    }
                }

                i = 0;
                std::cout << std::setw(4);
                if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i) < 0) {
                    if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i) == -3) {
                        std::cout << "-";
                    } else {
                        std::cout << "?";
                    }
                }
                else {
        //            std::cout << "";
                    for (i = 0; i < f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetNumStates(t, c); ++i) {
                        std::cout << f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t, c, i);
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    
}

void setup_reader(MultiFormatReader *reader)
{
    assert(reader != NULL);
    
    reader = new MultiFormatReader();
    
    NxsTaxaBlock        *taxa       = new NxsTaxaBlock;
    NxsAssumptionsBlock *assumpts   = new NxsAssumptionsBlock(taxa);
    NxsCharactersBlock  *chars      = new NxsCharactersBlock(taxa, assumpts);
    NxsTreesBlock       *trees      = new NxsTreesBlock(taxa);
    NxsDataBlock        *data       = new NxsDataBlock(taxa, assumpts);
    
    reader->Add(taxa);
    reader->Add(assumpts);
    reader->Add(chars);
    reader->Add(trees);
    reader->Add(data);
}


int main(int argc, const char * argv[]) {
    
    if (argc < 3) {
        std::cout << "DiffMatrix v 1.0" << std::endl;
        std::cout << "Compare two versions of a Nexus matrix." << std::endl;
        std::cout << "By Martin D Brazeau" << std::endl;
        std::cout << "No warranties or guarantees of any kind." << std::endl;
        std::cout << "\nUseage:" << std::endl;
        std::cout << "$ diffmatrix file1.nex file2.nex\n" << std::endl;
        return 0;
    }
    
    MultiFormatReader f1reader;
    MultiFormatReader f2reader;
    
    setup_reader(&f1reader);
    setup_reader(&f2reader);
    
    std::cout<< "Reading file: " << argv[1] << std::endl;
    f1reader.ReadFilepath(argv[1], MultiFormatReader::NEXUS_FORMAT);
    
    std::cout<< "Reading file: " << argv[2] << std::endl;
    f2reader.ReadFilepath(argv[2], MultiFormatReader::NEXUS_FORMAT);
    
    find_differences(f1reader, f2reader);
    
    return 0;
}
