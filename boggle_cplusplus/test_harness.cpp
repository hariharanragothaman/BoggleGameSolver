#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <locale>

#include "test_harness.h"

const int NUM_BRANCHES = 8;
const int ALPHA_SIZE = 26;
const int WSIZE = 20; 
const int BORDER = ALPHA_SIZE;
using namespace std;
char longestWord[WSIZE+1];


int main(int argc, const char** argv)
{
    char boggleFile[100] = "boggle.txt";             // I/P file that contains the matrix 
    char dictFile[100] = "dictionary.txt";	     // The complete dictionary word-list
    char resultsFile[100] = "results.txt";           // File to save results to check findings

    cout.imbue(std::locale("")); //adds commas to large numbers

    if( argc > 1 )
        strcpy(boggleFile, argv[1]);
    if( argc > 2 )
        strcpy(dictFile, argv[2]);


    // Load the Dicitionary List [ that contains all allowed words in the game ] 
    LoadDictionary( dictFile );

    beginning = clock();	
    Results output;

    output = FindWords(boggleFile, 4, 4);

    for(int i = 0; i < 100; i++)
    {
        cout << ".";
    }
    cout << " 100%" << endl;
    // Printing results from the Results Structure
    cout << "The number of words are: " << output.Count << endl;
    cout << "The Score is: " << output.Score << endl;
    
    
    // Printing some general results stuff
    cout << wordsParsed << " words parsed in " << dictFile << endl;
    cout << "Word length limit of " << WSIZE << " characters" << endl;
    cout << puzzle_size << " cubes on the board" << endl;

    double end = double(clock() - beginning) / CLOCKS_PER_SEC;
    double speed = 0;
    if( end )
        speed = floor((checkedNodes/end)/1000);
    cout << "Time taken (Nodes checked per ms) :" << speed << endl;
    cout << "Results saved to " << resultsFile << endl;
}
