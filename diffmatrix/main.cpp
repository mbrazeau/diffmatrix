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

typedef struct cdiff_s {
    unsigned tax1;
    unsigned tax2;
    unsigned charn;
} cdiff_s;

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
    std::vector<cdiff_s> diffs;
    
    int ntax1 = f1reader.GetTaxaBlock(0)->GetNTax();
    int nchar1 = f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetNCharTotal();
    
    int ntax2 = f2reader.GetTaxaBlock(0)->GetNTax();
    int nchar2 = f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetNCharTotal();
    
    if ((ntax1 != ntax2) || (nchar1 != nchar2)) {
        std::cout << "ERROR: matrices have different dimensions" << std::endl; // TODO: Give specifics. Ask to proceed.
        return;
    }
    
    unsigned int c;
    unsigned int t1;
    unsigned int t2;
    
    for (c = 0; c < nchar1; ++c) {
//        std::cout << "Character " << c + 1 << std::endl;
        
        for (t1 = 0; t1 < ntax1; ++t1) {
            // Get the character output
            int i = 0;
            
            // First, find the taxon in the opposite list
            for (t2 = 0; t2 < ntax2; t2++) {
                if (f1reader.GetTaxaBlock(0)->GetTaxonLabel(t1) == f2reader.GetTaxaBlock(0)->GetTaxonLabel(t2)) {
                    break;
                }
            }
            
            if (compare_cells(*f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0),
                              *f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)
                              , t1, c) == false)
            {
                cdiff_s d;
                d.tax1 = t1;
                d.tax2 = t2;
                d.charn = c;
                diffs.push_back(d);
            }
            
//            if (compare_cells(*f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0),
//                              *f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)
//                              , t1, c) == false)
//            {
//                std::cout << std::setw(20);
//                std::cout << f1reader.GetTaxaBlock(0)->GetTaxonLabel(t1);
//                std::cout << "\t";
//
//
//                if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, i) < 0) {
//                    if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, i) == -3) {
//                        std::cout << "-";
//                    } else {
//                        std::cout << "?";
//                    }
//                }
//                else {
//        //            std::cout << "\t";
//                    for (i = 0; i < f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetNumStates(t1, c); ++i) {
//                        std::cout << f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, i);
//                    }
//                }
//
//                i = 0;
//                std::cout << std::setw(4);
//                if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, i) < 0) {
//                    if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, i) == -3) {
//                        std::cout << "-";
//                    } else {
//                        std::cout << "?";
//                    }
//                }
//                else {
//        //            std::cout << "";
//                    for (i = 0; i < f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetNumStates(t2, c); ++i) {
//                        std::cout << f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, i);
//                    }
//                }
//                std::cout << std::endl;
//            }
        }
    }
    
    std::cout << std::endl;
    int i;
    int n = -1;
    for (i = 0; i < diffs.size(); ++i) {
        
        t1 = diffs[i].tax1;
        t2 = diffs[i].tax2;
        c = diffs[i].charn;
        
        if (c != n) {
            if (i != 0) {
                std::cout << std::endl;
            }
            std::cout << "Character " << c + 1 << std::endl;
        }
        
        std::cout << std::setw(20);
        std::cout << f1reader.GetTaxaBlock(0)->GetTaxonLabel(t1);
        std::cout << "\t";

        int k = 0;
        if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, 0) < 0) {
            if (f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, i) == -3) {
                std::cout << "-";
            } else {
                std::cout << "?";
            }
        }
        else {
//            std::cout << "\t";
            for (k = 0; k < f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetNumStates(t1, c); ++k) {
                std::cout << f1reader.GetCharactersBlock(f1reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t1, c, k);
            }
        }

        k = 0;
        std::cout << std::setw(4);
        if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, 0) < 0) {
            if (f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, i) == -3) {
                std::cout << "-";
            } else {
                std::cout << "?";
            }
        }
        else {
//            std::cout << "";
            for (k = 0; k < f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetNumStates(t2, c); ++k) {
                std::cout << f2reader.GetCharactersBlock(f2reader.GetTaxaBlock(0), 0)->GetInternalRepresentation(t2, c, k);
            }
        }
        std::cout << std::endl;
        
        n = c;
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
    
    std::cout << "DiffMatrix v 1.2" << std::endl;
    std::cout << "Compare two versions of a Nexus matrix." << std::endl;
    std::cout << "By Martin D Brazeau" << std::endl;
    std::cout << "No warranties or guarantees of any kind.\n" << std::endl;
    
    if (argc < 3) {
        std::cout << "Useage:" << std::endl;
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
