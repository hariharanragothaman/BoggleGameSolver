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

1. `Makefile`             :   Orchestrates the compile, build, clean process                                  
2. `BoggleSolver.cpp`     :   Houses the logic for the BoggleSolver                               
3. `BoggleGenerator.cpp`  :   Houses the logic for generating a random board and writing it to a file.                 
4. Creating a shared library and writing our own test-harness               
