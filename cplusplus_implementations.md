### Overview of the general implementation

From what I understand from the question - we have to implement API's with defined function signatures.                 
These API's will be run against a test harness.               

#### Solution Steps Overview:                
1. Implement the solution.            
2. Compile and Run      
3. Create a static (or) shared library that the test-harness can use for various board sizes              
   This can also be used by other interested programs, kinda serves like an SDK.      
4. Run some tests against the solution, benchmarking.                   

#### Code Run-Through:                       

1. Given I/P and function signatures            
2. `Makefile`             :   Orchestrates the compile, build, clean process                                  
3. `boggle_solver.cpp`     :   Houses the logic for the BoggleSolver                               
4. `boggle_generator.cpp`  :   Houses the logic for generating a random board and writing it to a file.                 
5. Creating a shared library and writing our own test-harness               

1. We have been given specific format to return the results found after solving 
```
struct Results
{
	const char* const* Words;
	unsigned Count;
	unsigned Score;
	void* UserData;
};
```

2. In `boggle_solver.cpp`:  **Note**: This contains all the `TODO` functions required to be implemented:         
Let's take a look at the code-flow here:                  
Here we have `class Trie` and several helper functions to implement Trie.                                

`class Trie` implements the `Trie` datastructure                            
    1. We create a pointer to object of this class.                    
    2. `insertWord` adds words into the Trie.      
    3. `bool found` - Flag to check if the word has been found, to mark it in Trie
    4. `lookup` - To keep track of which word has been found and also duplicates

Order of Function call:                    

`LoadDictionary` loads the entire word list into memory with the help of `readFile` function.                                           
c. We call `FindWords` function to find all words in the              

`FindWords` - call flow:                      
1. `buildBoard`    : Builds the board from the generated file, that contains random characters
2. `traverseBoard` : Calls  `DFS`  --> Calls   --> `lookup`                                          
3. `getFoundWords` : Parses the Trie, and checks if the 'found' flag is True, which marrks that it's a word - and if it's pushes into the `<vector>` collecting the different words 

`FindWords` returns output of the type `Results` structure as specified in the problem statement.                   
So what do `traverseBoard`, `descend`, `lookup` and `getFoundWords` do?                       
> That brings us to the core solution implementation of the problem which does a Depth-First-Search           
> This is very similar to how we have solved it in python, the implementation style is different.   

`traverseBoard` - basically `DFS` for every letter in the generated boggle board.
`DFS` - returns the number of words found when parsing the Trie, by performing depth-first-search
