import string
from random import choice


class PrefixTree:
    def __init__(self, letter=None):
        self.letter = letter
        self.children = {}
        self.is_word = False

    def insert(self, word):
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
        if letter not in self.children:
            return None
        return self.children[letter]


class BoggleBoard:
    def __init__(self, board=None, board_size=3):
        self.board_size = 3
        self.board = []
        if board is None:
            self.board = [[choice(string.ascii_lowercase) for cols in range(board_size)] for rows in range(board_size)]
            print("The generated board is:", self.board)
        else:
            self.board = board

    def solve_boggle(self, trie, result):
        for rows in range(self.board_size):
            for cols in range(self.board_size):
                self.search_tree(trie, result, rows, cols)

    def search_tree(self, trie, result, row, col, path=None, node=None, word=None):
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
    with open('words.txt', encoding='latin-1') as f:
        for word in f.readlines():
            if len(word) > 3:
                word = word.rstrip().lower()
                trie.insert(word)


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
