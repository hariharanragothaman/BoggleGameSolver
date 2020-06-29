#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <locale>

using namespace std;

const int NUM_BRANCHES = 8;
const int ALPHA_SIZE = 26;
const int WSIZE = 20; 
const int BORDER = ALPHA_SIZE;


/********************************************************************************
 * Structure format for returning the result after solving the game of boggle
 * This format is given as part of the problem statement
 *******************************************************************************/

struct Results
{

	const char* const* Words;
	unsigned Count;
	unsigned Score;
	void* UserData;
};


/**************************
 * Function Declarations
 *************************/

void LoadDictionary(const char* path);
void FreeDictionary();

void * buildBoard(const char boggleFile[]);
void traverseBoard();

Results FindWords(const char* board, unsigned width, unsigned height);
void FreeWords(Results results);


// OTHER DECLARATIONS - NEEDED 
int duplicates = 0;
int wordsParsed = 0;
int checkedNodes = 0;
int progress = 0;
int onePercentage;
char longestWord[WSIZE+1];
clock_t beginning; //used to time search duration
int * board;
int board_size;
int puzzle_size;
int cols;
int * SEARCHED;
int * children;
vector<char*> found;


/*********************************************************************************
 * @brief: Trie class implement the Trie Data Structure
 * :member: count 	- number of suffixes that share the letter as root
 * :member: word  	- if a node completes a word, it gets stored here
 * :memeber:found 	- boolean flag to check if the the node completes a word and if it has been found.
 * :function: Trie() 	- constructor assigns all children to NULL by default
 *                        Each letter can have a maximum of 26 links
 *********************************************************************************/

class Trie
{
	public:
		Trie* children[ALPHA_SIZE];
		Trie* parent;
		int count;
		char* word;
		bool found; 
		
		Trie();
};

Trie::Trie()
{
	count = 0;
	word = NULL;
	found = false;
	
	int i;
	for(i = 0; i < ALPHA_SIZE; i++)
	{
		children[i] = NULL;
	}
}

// Pointer to  Trie Class is created
Trie* dict; 


/********************************************************************************
 * @brief: insertWord Function - loads the words in the dictionary into Trie
 *         This function essentially loads the dictionary into the Trie & 
 *         is called by LoadDictionary() function
 * :param: word[] - word to be inserted
 * :param: len	  - length of the word		
 *
 *********************************************************************************/


void insertWord( char word[], const int len ){
    Trie* p = dict;
    int i;

    for(i = 0; word[i]; i++)
    {
        int letter = word[i] - 'a'; //convert characters to ints: a=0 z=25

        //combine 'qu' into single cube represented by 'q'
        if( ('q' == word[i]) && ('u' == word[i+1]) )
            i++;

        p->count++; //track how many words use this prefix

        if( !p->children[letter] )
            p->children[letter] = new Trie;

        p->children[letter]->parent = p;

        p = p->children[letter];
    }

    p->word = word; //the last node completes the word, save it here
}

/************************************************************************************************
 * @brief: getFoundWords function parses the Trie to add found words into resultant vector
 * :param: p - pointer to object of class Trie
 ************************************************************************************************
 */

void getFoundWords(Trie* p)
{
    int i;

    if( p )
    {
        if( p->found )
            found.push_back( p->word );

        for(i = 0; i < ALPHA_SIZE; i++)
	{
            getFoundWords( p->children[i] );
        }
    }
}



//*****************************************************************************************************************
/******************************************************************************************************************
 * @brief: Function to read file completely into buffer
 *  	   This is used to read both the dictionary file [ complete word list]
 *         This is also used to I/P file containing the list of letters
 *
 * :param fname: The file to be read into memory
 *
 ******************************************************************************************************************/

char* readFile( const char *fname)
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen ( fname , "r" );
    if (pFile==NULL)
    {
	    fputs ("File error",stderr); 
	    exit (1);
    }

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) 
    {
	    fputs ("Memory error",stderr); 
	    exit (2);
    }

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) 
    {
	    fputs ("Reading error",stderr); 
	    exit (3);
    }

    /* the whole file is now loaded in the memory buffer. */

    fclose (pFile);
    return buffer;
}

/**********************************************************************************************
 *
 * @brief: saveResults: Dumps the necessary results into a file
 * :param fname: File name where results have to dumped into.
 *
 **********************************************************************************************/

void saveResults( char fname[] ){
    FILE * file;
    file = fopen (fname,"w");

    char c;
    for(int i = 0; i < board_size; i++)
    {
        c = (char) (board[i] + 'a');
        if( 'q' == c )
	{
            fputs("Qu",file);
        }
	else if( BORDER == board[i] )
	{
            fputs("* ",file);
        }
	else
	{
            fputc(c,file);
            fputs(" ",file);
        }
        if( (i+1) % cols == 0 ) fputs("\n",file);
    }
    fputs("\n",file);

    sort(found.begin(), found.end());

    for(vector<char*>::iterator it = found.begin(); it != found.end(); ++it) 
    {
            fputs (*it,file);
            fputs ("\n",file);
    }
    fclose(file);
}

// ****************************************************************************************************************

void statusBar(int i)
{
    if( (cols-2) < 100 )
        return;
    i += 1; 

    if( i - progress == onePercentage )
    {
	    cout << "|" << flush;
	    progress += onePercentage;
    }

    if( i == puzzle_size ) 
    {
	    cout << " done!" << endl;
    }
}

/*****************************************************************************************************************
 *
 * @brief: Converts an input vector to character array
 *	   Creates an objects of the structure Results.
 *	   Stores the value of 'Count' and 'Score' in the structure
 *	   This function is called by FindWords() function
 *
 * :param: wordsFound: vector of char* of words that have been found
 * :return: returnType is of Results struct
 *
 *****************************************************************************************************************/

Results vectorToCharArray(vector<char *> wordsFound)
{
	Results res;
       	char** par2 = new char* [wordsFound.size() + 1];
	for (size_t i = 0; i < wordsFound.size(); ++i)
	{
		par2[i] = strdup(wordsFound[i]);
		long unsigned int length = strlen(wordsFound[i]);
		switch(length)
		{
			case 3:
			case 4:
				res.Score++;
				break;
			case 5:
				res.Score += 2;
				break;
			case 6:
				res.Score += 3;
				break;
			case 7:
				res.Score += 5;
				break;
			default:
				res.Score += 11;
				break;
		}

	}

	const char* const* ptrr = (const char* const*)par2;
	/*
	for (size_t i = 0; i < par2Vect.size(); i++)
		printf("%s", *(ptrr + i));
	*/

	res.Count = wordsFound.size();
	res.Words = ptrr;
	return res;

}

/****************************************************************************************************************
 * 
 * @brief: FindWords() function - the direct function that is called to find all words in boggleBoard
 *         Internally calls the following functions
 *         1. buildBoard()
 *         2. traverseBoard()
 *         3. getFoundWord()
 *         4. vectorToCharArray() 
 *
 *         This is the API that will be tied to the test harness
 *
 * :return: object of type Results
 *
 ****************************************************************************************************************/


Results FindWords(const char* board, unsigned width, unsigned height)
{
	Results output;
	// Add try-catch to see if width & height are same...
	if (width != height)
	{
		throw std::invalid_argument("Width and Height have to be equal"); 
	}
	buildBoard(board);
    	traverseBoard();
    	getFoundWords( dict );

	output = vectorToCharArray(found);	
	return output;

}

/*
 * @brief: Reads the boggle.txtfile using the readFile function() and creates the boggleboard
 *	   Also neatly adds a border around the matrix generated for pretty-printing
 */

void * buildBoard(const char boggleFile[])
{
    char * buffer = readFile( boggleFile );
    int len = strlen( buffer );
    cols = sqrt( len ) + 2;
    
    children = new int[NUM_BRANCHES] {-1-cols, -cols, 1-cols, -1, 1, cols-1, cols, cols+1};
    
    board_size = cols * cols;
    puzzle_size = (cols-2) * (cols-2);
    
    onePercentage = double(1) / 100 * puzzle_size;
    board = new int[board_size];

    int j = 0;
    for(int i = 0; i < board_size; i++)
    {
        if( (i < cols) || ((i+1) % cols == 0) || (i > cols * (cols -1)) || (i % cols == 0) )
	{ 
            board[i] = BORDER;
        }
	else
	{
            board[i] = buffer[j] - 'a';
            j++;
        }
    }
}


//********************************************************************************************
/*********************************************************************************************
 *  @brief: Load dictionary into trie
 *  	    I/P Dictionary is a file with one word per line
 *  
 *  :param dictFile: I/P dictionary file containng words
 *  		     File that will be read, and where words will be inserted into Trie
 *********************************************************************************************/

void LoadDictionary(const char* dictFile)
{
    char * buffer = readFile( dictFile );
    char * word;
    int len, i;

    dict = new Trie;

    word = strtok(buffer,"\n\t");
    while (word != NULL) {
        len = strlen( word );
        if( len >= 3 )
	{	
		// According to Boggle rules - word length should be atleast 3
		insertWord( word, len );
		wordsParsed++;
        }

        word = strtok (NULL, "\n\t");
    }
}

/* 
 * @brief: Helper Function to free the created pointer to Trie Class
 *
 */

void FreeDictionary()
{
   delete dict;
}

//************************************************************************************************************
// CORE -LOGIC BEGINS HERE 

/*
 * @brief: lookup()
 */

inline Trie* lookup(const int i, Trie* p)
{
    p = p->children[i];
    if( p && p->word )
    {
	    if( p->found )
	    {
		    duplicates++;
	    }
	    else
	    {
		    p->found = true;
		    p->parent->count--; //decrement how many words are left that use this prefix
	    }
    }
    return p;
}

/*
 * @brief DFS() 
 */

inline bool DFS(int cubeIndex, Trie* p, vector<bool> searched)
{
    ++checkedNodes;
    p = lookup( board[cubeIndex], p);

    if( p && p->count )
    {
	    //is this a valid prefix? Are there any remaining words that use it?
	    searched[cubeIndex] = true; //mark this cube as 'visited'
	    for(int i = 0; i < NUM_BRANCHES; i++)
	    { 
		    //DFS to each neighboring cube
		    int child = cubeIndex + children[i];
		    if((board[child] != BORDER) && !searched[child])
			    DFS(child, p, searched);
	    }
    }
}



/*************************************************************************************************
 *
 * @brief: TraverseBoard() - For each cube on the board, perform a depth first search using DFS()
 *
 **************************************************************************************************/
 
 void traverseBoard()
{
    Trie* p = dict;
    vector<bool> searched; //cubes should be used only once per word
    int i, j = 0;

    //initialize searched to false for all cubes on the board
    for(int i = 0; i < board_size; i++)
    { 
	    searched.push_back(false);
    }

    for(int i = 0; i < board_size; i++)
    { 
	    if(board[i] != BORDER)
	    {
		    DFS(i, p, searched);
		    statusBar(j);
		    ++j;
	    }
    }
}


// ****************************************************************************************************************
/******************************************************************************************************************
 * @brief:  main() function
 * 	    DRIVER code to test our implementations
 * 	    This is used to test the logic of the implemented API
 *
 *****************************************************************************************************************/



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
    saveResults( resultsFile);
    cout << "Time taken (Nodes checked per ms) :" << speed << endl;
    cout << "Results saved to " << resultsFile << endl;
}
