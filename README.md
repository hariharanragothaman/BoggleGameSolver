# BoggleGameSolver    
Algorithm Solution Approaches for solving Boggle       

### General Prologue                              
---------------------                                                  
1. All general requriements by the problem statement, TODO functions have been satisfied.                                                                  
2. Time Complexity: O(n) where n is the length of the word to be found.                                                                                         
3. Technologies used: C++, Python                                          
4. Basic requriements to test C++ solution: Ubuntu 16.04 LTS, g++/gcc/gnu++ compilers have to be installed.                                                     
5. Basic requirements to test python solution: Ubuntu 16.04 LTS, python3.8 installed.                                                 
6. BONUS1: Attempted to benchmark and compare C++ vs Python implementation, and time it takes as size of the board increases.                               
7. BONUS2: Created shared libraries and test_harnesses to see if the implemented code can be plugged in as an API                          
**Note**: `Makefile` and `README.md` have detailed instructions on how to run the programs.                      

### Table of Contents
----------------------
1. What's the actual solution to the problem?     
2. Pythonic Approach     
3. C++ Approach     
4. Benchmarking Analysis and Performance   
5. Some Automation Tests / Approaches
6. References
7. Possible Enhancements

#### Actual Solution to the problem (Using a Trie Data Structure)           
In both the implementations we have used the 'Trie' approach. Tries are generally the efficient way to search for words pruning search space.               
The time complexity here is: O(n) where n is the length of the string to be found.               

Trie is essentially a tree where each node can have atmost 26 children (values from the alphabet).    
It will also contain a boolean field (or) binary field - to indicate if it's the end letter of a word, or if it's a prefix.
The root of the Trie, is generally a <NULL> node or a recognized node.

General operations in a trie:   
1. Insert value in a Trie    
2. Search for a value in a Trie   
3. Check for a prefix in a Trie     


#### Pythonic Approach            
The pythonic approach is explained in detail here: [Python Walk-Through](https://github.com/hariharanragothaman/BoggleGameSolver/blob/master/python-implementation.md)                 

#### C++ Approach    
The C++ approach is explained in detail here: [C++ Walk-Through](https://github.com/hariharanragothaman/BoggleGameSolver/blob/master/cplusplus_implementations.md)                  

#### Benchmarking Analysis and Performance          
Benchmarking analysis findings are documented here: [Benchmarking Findings](https://github.com/hariharanragothaman/BoggleGameSolver/blob/master/benchmarking.md)          

#### Building and Running the C++ application   
1. Pre-requisites / Development setup               
      a. Currently I am using both `-std=c++11` and `-std=gnu++0x` for building the applications.          
      b. Using Ubuntu 16.04 LTS to build and test the C++ program.          
      c. Please after building the shared library for the test-harness,    
         please export `LD_LIBRARY_PATH` and if needed include it in `/usr/lib` and `/usr/local/lib`     


2. Using the Boggle Generator   
```
$ cd boggle_cplusplus
$ make generate
$ ./boggle_generator 10
Created boggle board boggle.txt
```

3. Using the Boggle Solver
```
$ make solve

g++ -o boggle_solver boggle_solver.cpp -std=gnu++0x
./boggle_solver
.................................................................................................... 100%
The number of words are: 1,518
The Score is: 3,939
178,590 words parsed in dictionary.txt
Word length limit of 20 characters
100 cubes on the board
Time taken (Nodes checked per ms) :725
Results saved to results.txt
```

4. Creating the shared library for potential use with Test Harness    

This creates the shared library - boggle_solver.so
```
$ make shared
```
I have written a simple test-harness for testing my application - `test.cpp`      
To compile that with the shared library

```
$ make test
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/scratch/BoggleGameSolver/boggle_cplusplus/boggle_solver.so
$ sudo cp /home/scratch/BoggleGameSolver/boggle_cplusplus/boggle_solver.so /usr/lib
$ sudo cp /home/scratch/BoggleGameSolver/boggle_cplusplus/boggle_solver.so /usr/local/lib
```

5. Using the Dummy Test Harness   
```
$ ./test
.................................................................................................... 100%
The number of words are: 1,518
The Score is: 3,939
178,590 words parsed in dictionary.txt
Word length limit of 20 characters
100 cubes on the board
Time taken (Nodes checked per ms) :726
Results saved to results.txt
```

#### Running the python application          

Steps to run python program      
```
$ cd boggle_python/
$  python3.8 boggle_solver_trie_implementation.py
```
Sample O/P:

```
Enter the size of the boggle board 4
The generated board is: [['z', 'd', 'm', 'j'], ['z', 'h', 'h', 'n'], ['c', 'k', 'm', 'b'], ['r', 'i', 'g', 'n']]
The words are: ['khz']
The number of words found are: 1
```

#### Some Automation Test - To Double-check Results     


#### References     
1.http://boardgamegeek.com/thread/300883/letter-distribution      
2. Several resources in StackoverFlow and Google    
3. https://en.wikipedia.org/wiki/Boggle   
4. https://en.wikipedia.org/wiki/Trie


#### Possible Enhancements to the Submission                       
1. We can use unit++, google-test frameworks to test negative test case scenarios.                                    
2. We can possibly host the boggleboard in the cloud, as an available service for users to solve.                    
3. We can add CI/CD support for the respository and link it with web-hooks to trigger checks.    
4. Documentation can be improved through open-source tools like - `doxygen` , `xslt` (or) `Sphinx`


