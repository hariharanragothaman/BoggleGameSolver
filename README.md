# BoggleGameSolver    
Algorithm Solution Approaches for solving Boggle       


### Table of Contents
----------------------
1. What's the actual solution to the problem?     
2. Pythonic Approach     
3. C++ Approach     
4. Benchmarking Analysis and Performance      
5. References    

#### Actual Solution to the problem (Using a Trie Data Structure)           
In both the implementations we have used the 'Trie' approach                            

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


