#include <iostream>
#include "ncl.h"

#include <algorithm>
#include <string>
#include <cctype>
#include <vector>

void show_info(void)
{
    std::cout <<
        "\n\n"
        "    Diffmatrix 2.2 by Martin D. Brazeau\n"
        "    Compares two input Nexus files and outputs differences\n\n"
        "    Useage: ./diffmatrix file1.nex file2.nex\n\n"
        "    This is free software. You are welcome to use, modify, and distribute without fees\n"
        "    as long as the original author is credited.\n"
        "    No warranties or guarantees of any kind.\n\n"
        ;
}

void reader_init(MultiFormatReader *reader)
{
    NxsTaxaBlock *taxa = new NxsTaxaBlock;
    NxsAssumptionsBlock *assumpts = new NxsAssumptionsBlock(taxa);
    NxsCharactersBlock *chars = new NxsCharactersBlock(taxa, assumpts);
    
    reader->Add(taxa);
    reader->Add(assumpts);
    reader->Add(chars);
//    reader->Add(new NxsTreesBlock(taxa));
   // reader->Add(new NxsDataBlock(taxa, assumpts));
}

int compare_labels(NxsString l1, NxsString l2)
{
    NxsString nsp1, nsp2;

    if (l1 == l2) {
        return 0;
    }

    nsp1 = l1;
    nsp2 = l2;
    
    nsp1.erase(std::remove_if(nsp1.begin(), nsp1.end(), ::isspace), nsp1.end());
    nsp2.erase(std::remove_if(nsp2.begin(), nsp2.end(), ::isspace), nsp2.end());

    if (nsp1 == nsp2) {
        return 0;
    }

    return -1;
}

int find_character_index(NxsString label, NxsCharactersBlock &chars)
{
    int i, ret = -1;

    for (i = 0; i < chars.GetNCharTotal(); ++i) {
        if (!compare_labels(label, chars.GetCharLabel(i))) {
            ret = i;
            break;
        }
    }

    return ret;
}

void compare_taxon_sets(MultiFormatReader &origfile, MultiFormatReader &newfile)
{
    // Compare the taxa
    int origntax = origfile.GetTaxaBlock(0)->GetNTax();
    int newntax = newfile.GetTaxaBlock(0)->GetNTax();

    std::cout << "File 1 has: " << origntax << " taxa; File 2 has: " << newntax << " taxa.\n";
    
    int i, j;
    for (i = 0; i < origntax; ++i) {
        NxsString taxon;
        taxon = origfile.GetTaxaBlock(0)->GetTaxonLabel(i);
        for (j = 0; j < newntax; ++j) {
            //if (taxon == newfile.GetTaxaBlock(0)->GetTaxonLabel(j)) {
            if (!compare_labels(taxon, newfile.GetTaxaBlock(0)->GetTaxonLabel(j))) {
                break;
            }
        }
        if (j == newntax) {
            std::cout << "Taxon deleted: " << taxon << "\n";
        }
    }
    
    for (i = 0; i < newntax; ++i) {
        NxsString taxon;
        taxon = newfile.GetTaxaBlock(0)->GetTaxonLabel(i);
        for (j = 0; j < origntax; ++j) {
            if (taxon == origfile.GetTaxaBlock(0)->GetTaxonLabel(j)) {
                break;
            }
        }
        if (j == origntax) {
            std::cout << "Taxon added: " << taxon << "\n";
        }
    }
}

void compare_character_sets(MultiFormatReader &origfile, MultiFormatReader &newfile)
{
    int i, j;
    NxsCharactersBlock *origchars = origfile.GetCharactersBlock(origfile.GetTaxaBlock(0), 0);
    NxsCharactersBlock *newchars = newfile.GetCharactersBlock(newfile.GetTaxaBlock(0), 0);

    std::cout << "File 1 has: " << origchars->GetNCharTotal() << " characters; File 2 has: " << newchars->GetNCharTotal() << " characters.\n";

    // Linear search for each original character in the list of new characters. If not found, character deleted.
    std::cout << "\nCharacters deleted:\n";
    for (i = 0; i < origchars->GetNCharTotal(); ++i) {
        NxsString charlabel = origchars->GetCharLabel(i);
        int idx;
        idx = find_character_index(charlabel, *newchars);
        if (idx < 0) {
            std::cout << "Character "<< i + 1 << " (" << charlabel.substr(0, 80) << ") deleted.\n";
        }
    }

    // Linear search for each character from new dataset in the old one. If not found, character is new/added.
    std::cout << "\nCharacters added:\n";
    for (i = 0; i < newchars->GetNCharTotal(); ++i) {
        NxsString charlabel = newchars->GetCharLabel(i);
        int idx;
        idx = find_character_index(charlabel, *origchars);
        if (idx < 0) {
            std::cout << "Character "<< i + 1 << " (" << charlabel.substr(0, 80) << ") added.\n";
        }
    }
}

void compare_scores(MultiFormatReader &origfile, MultiFormatReader &newfile)
{
    int i, j, k, m;

    int origntax = origfile.GetTaxaBlock(0)->GetNTax();
    int newntax = newfile.GetTaxaBlock(0)->GetNTax();

    NxsCharactersBlock *origchars = origfile.GetCharactersBlock(origfile.GetTaxaBlock(0), 0);
    NxsCharactersBlock *newchars = newfile.GetCharactersBlock(newfile.GetTaxaBlock(0), 0);

    std::cout << "\nComparing scores...\n";
    std::cout << "Taxon, Orig. char. no., New char. no., Character label, Old state, New state\n";
    for (i = 0; i < origchars->GetNCharTotal(); ++i) {
        NxsString charlabel = origchars->GetCharLabel(i);
        // Find the same character
        for (j = 0; j < newchars->GetNCharTotal(); ++j) {
            if (charlabel == newchars->GetCharLabel(j)) {
                // Now compare taxon by taxon
                for (k = 0; k < origntax; ++k) {
                    NxsString taxon;
                    taxon = origfile.GetTaxaBlock(0)->GetTaxonLabel(k);
                    for (m = 0; m < newntax; ++m) {
                        if (taxon == newfile.GetTaxaBlock(0)->GetTaxonLabel(m)) {
                            // Found the taxon character cell
                            if (origchars->GetNumStates(k, i) == newchars->GetNumStates(m, j) == 1) {
                                char ostate = origchars->GetState(k, i, 0);
                                int ostateidx = origchars->GetInternalRepresentation(k, i, 0);
                                char nstate = newchars->GetState(m, j, 0);
                                int nstateidx = newchars->GetInternalRepresentation(m, j, 0);

                                if (ostate != nstate) {
                                    NxsString ostatelabel = "";
                                    NxsString nstatelabel = "";

                                    if (ostateidx >= 0) { 
                                        ostatelabel = origchars->GetStateLabel(i, ostateidx);
                                    } else { 
                                        if (ostateidx == -2) {
                                            ostatelabel = "missing";
                                        }
                                        if (ostateidx == -3) {
                                            ostatelabel = "inapplic.";
                                        }
                                    }

                                    if (nstateidx >= 0) {
                                        nstatelabel = newchars->GetStateLabel(j, nstateidx);
                                    } else {
                                        if (nstateidx == -2) {
                                            nstatelabel = "missing";
                                        }
                                        if (nstateidx == -3) {
                                            nstatelabel = "inapplic.";
                                        }
                                    }


                                    std::cout << "\"" << origfile.GetTaxaBlock(0)->GetTaxonLabel(k) <<"\",\""
                                        << i+1 << "\",\"" << j + 1 <<  "\",\"(" << charlabel.substr(0, 80) << ")\""
                                        << ",\"" << ostate << " (" << ostatelabel << ")\",\"" << nstate << " (" << nstatelabel << ")\"\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void compare_nexus(MultiFormatReader &origfile, MultiFormatReader &newfile)
{
    std::cout << "\n\n Comparing the data ....\n\n";
    // Compare the dimensions of the two datasets
    compare_taxon_sets(origfile, newfile);
    compare_character_sets(origfile, newfile);
    compare_scores(origfile, newfile);

}

int main(int argc, const char * argv[])
{
    // First, do argument checks.
    // Return error if argc is not right
    if (argc != 3) {
        show_info(); 
        return 0;
    }
    
    MultiFormatReader origfile;
    MultiFormatReader newfile;

    reader_init(&origfile);
    reader_init(&newfile);

    try {
        origfile.ReadFilepath(argv[1], MultiFormatReader::NEXUS_FORMAT);
    }
    catch (NxsException &e) {
        std::cout << e.what() << std::endl;    
        return 1;
    }

    try {
        newfile.ReadFilepath(argv[2], MultiFormatReader::NEXUS_FORMAT);
    }
    catch (NxsException &e) {
        std::cout << e.what() << std::endl;    
        return 1;
    }
    
    compare_nexus(origfile, newfile);

    return 0;
}

