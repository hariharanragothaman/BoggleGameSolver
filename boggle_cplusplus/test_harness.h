#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <locale>

struct Results
{

	const char* const* Words;
	unsigned Count;
	unsigned Score;
	void* UserData;
};

/*
 *
 * Function Declarations
 *
 *
 */

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
clock_t beginning; //used to time search duration
int * board;
int board_size;
int puzzle_size;
int cols;
int * SEARCHED;
int * children;
