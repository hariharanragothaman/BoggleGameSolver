import string
from random import choice

class PrefixTree:
    """
    This class implements the Trie DataStructure also called as PrefixTree
    """
    def __init__(self, letter=None):
        self.letter = letter
        self.children = {}
        self.is_word = False

    def insert(self, word):
        """
        @brief: Function to insert word into Trie data structure
        :param: word - word in the dictionary
        """
        if len(word):
            letter = word[0]
            word = word[1:]
            if letter not in self.children:
                self.children[letter] = PrefixTree(letter)
            return self.children[letter].insert(word)
        else:
            self.is_word = True
            return

    def find_children(self, letter):
        """
        @brief: Function to return children of a given letter
        """
        if letter not in self.children:
            return None
        return self.children[letter]


class BoggleBoard:
    """
    BoggleBoard class that takes care of boggleboard related operations
    """
    def __init__(self, board=None, board_size=3):
        """
        @brief: Constructor
        Function generates a boggle board of given size of defined board_size
        :param: board - If I/P board of 2D Matrix is provided
        :param: board_size - default value is 3 - thereby having 9 cubes.
        """
        self.board_size = 3
        self.board = []
        if board is None:
            self.board = [[choice(string.ascii_lowercase) for cols in range(board_size)] for rows in range(board_size)]
            print("The generated board is:", self.board)
        else:
            self.board = board

    def solve_boggle(self, trie, result):
        """
        @brief: Function that solves the boggle board
                Calls search_tree that performs DFS on every boggle cube
        :param: trie - Object of PrefixTree class
        :aram result - set() to store the result
        """
        for rows in range(self.board_size):
            for cols in range(self.board_size):
                self.search_tree(trie, result, rows, cols)

    def search_tree(self, trie, result, row, col, path=None, node=None, word=None):
        """
        @brief: Function to search for words in the boggleboards
        :param: trie - PrefixTree class object
        :param: result - set() to add words into
        :param: row - row index in board
        :param: col - column index in board
        :param: node - children of a letter selected 
        :param: word - generated word as we parse the Trie
        """
        letter = self.board[row][col]

        if node is None or path is None or word is None:
            node = trie.find_children(letter)
            path = [(row, col)]
            word = letter
        else:
            node = node.find_children(letter)
            path.append((row, col))
            word += letter

        if node is None: return
        elif node.is_word: result.add(word)

        for r in range(row - 1, row + 2):
            for c in range(col - 1, col + 2):
                if 0 <= r < self.board_size and 0 <= c < self.board_size and (r, c) not in path and not (
                        r == row and c == col):
                    self.search_tree(trie, result, r, c, path[:], node, word[:])


def load_word_list(trie):
    """
    Function to load the dictionary into the Trie
    """
    with open('dictionary.txt', encoding='latin-1') as f:
        for word in f.readlines():
            if len(word) > 3:
                word = word.rstrip().lower()
                trie.insert(word)

def run_benchmark():
    """
    @brief: Function to run some benchmarks
    """
    for i in range(3, 100):
        bg = BoggleBoard(board_size=i)
        trie = PrefixTree()
        load_word_list(trie)
        result = set()
        start = time.time()
        bg.solve_boggle(trie, result)
        end = time.time()
        time_taken = end - start
        print(end - start)

if __name__ == '__main__':
    n = int(input("Enter the size of the boggle board"))
    """
    Example boggle_board given:
    boggle_board = [['d', 'z', 'x'],
                    ['e', 'a', 'i'],
                    ['q', 'u', 't']]
    """
    bg = BoggleBoard(board_size=n)
    trie = PrefixTree()
    load_word_list(trie)

    result = set()
    bg.solve_boggle(trie, result)

    print("The words are:", sorted(result))
    print("The number of words found are:", len(result))
