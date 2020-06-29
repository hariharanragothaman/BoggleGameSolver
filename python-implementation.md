#### Running through the python code    

In this implementation we have 2 classes:      
1. `PrefixTree`        
2. `BoggleBoard`         

`PrefixTree` class essentially implements the Trie data structure.                     
`BoggleBoard` class aims at solving the Boggle Board that has been generated.

Memeber functions in `class PrefixTree`:
1. `__init__`: Constructor that helps in defining the basic structure of the Trie node
2. `insert`:   Add every letter of every word into the Trie data structure
3. `find_children`: Returns letters connected to a specific letter aka, it's children     

Memeber functions in `class BoggleBoard`:                          
1. `__init__`:  Constructor that helps in creating a randomized word of givne size (default min: 3)
2. `solve_boggle`:  Basically, call `search_tree` for every index in the boggle board
3. `search_tree`: Implements DFS to search for the word in Trie

We have other helper functions such as:              
1. `load_word_list`: This loads the entire word list / dictionary into memory and we insert each word into Trie.                 
2. `run_benchmark`: Helps in calculating how long it takes to solve for varying board sizes.             
