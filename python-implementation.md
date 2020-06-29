#### Running through the python code    

In this implementation we have 2 classes:      
1. `PrefixTree`        
2. `BoggleBoard`         

`PrefixTree` class essentially implements the Trie data structure.                     
`BoggleBoard` class aims at solving the Boggle Board that has been generated.

Memeber functions in `class PrefixTree`:
1. Constructor:
2. `insert`:      
3. `find_children`:       

Memeber functions in `class BoggleBoard`:                          
1. Constructor:  
2. `solve_boggle`:  
3. `search_tree`:    

We have other helper functions such as:              
1. `load_word_list`: This loads the entire word list / dictionary into memory and we insert each word into Trie.                 
2. `run_benchmark`: Helps in calculating how long it takes to solve for varying board sizes.             
