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

