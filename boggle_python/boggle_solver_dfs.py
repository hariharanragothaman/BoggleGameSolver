"""
Solution to the Boggle Game - A pythonic implementation
"""
import string
from collections import defaultdict
from random import choice

def create_boggle_board(board_size=3):
    """
    Function to create the randomized boggle board
    :param board_size: The size of the boggle board - creating an size x sixe grid
    :return: list of lists (matrix) - aka the boggle board
    """
    boggle_board = [[choice(string.ascii_lowercase) for cols in range(board_size)] for rows in range(board_size)]
    return boggle_board

def display_boggle_board(boggle_board):
    for rows in boggle_board:
        print(rows)

def get_word_list(file_name="words.txt"):
    """
    Function to create the map - from the word-list
    :param file_name: I/P Dictionary file name
    :return: hash-map / adjacency list of words along with their starting characters
    """
    hash_map = defaultdict(list)
    with open(file_name) as f:
        for word in f.readlines():
            if len(word) > 3:
                word = word.rstrip().lower()
                hash_map[word[0]].append(word.strip())
    return hash_map

def is_word_valid(word, hash_map):
    """
    :param word:
    :param hash_map:
    :return:
    """
    return word in hash_map[word[0]]

def get_prefix_match(word, hash_map):
    """
    :param word:
    :param hash_map:
    :return:
    """
    return [char for char in hash_map[word[0]] if char.startswith(word)]

def get_neighbours(boggle_board, r, c):
    """
    :param boggle_board: The I/P Boggle board - 2D matrix
    :param row: index of row
    :param col: index of column
    :return:
    """
    board_size = len(boggle_board)
    neighbours = [[(r - 1, c - 1), (r - 1, c), (r - 1, c + 1)],
                  [(r, c - 1), (r, c + 1)],
                  [(r + 1, c - 1), (r + 1, c), (r + 1, c + 1)]]
    if c == 0:
        # left edge -> keep the 2 rightmost columns
        res = [n[1:] for n in neighbours]
    elif c == board_size - 1:
        # right edge -> keep the two leftmost colums
        res = [neighbours[0][0:2], [neighbours[1][0]], neighbours[2][0:2]]
    else:
        # somewhere in the grid, keep everything
        res = neighbours

    if r == 0:
        # top edge of the grid -> keep the bottom two rows
        res = res[1:]
    elif r == board_size - 1:
        # bottom edge -> keep the top two rows
        res = res[0:2]
    else:
        pass

    # now we have a correct list of the indices we need, create the necessary tuples

    letters = []
    for row in res:
        letters.extend([(boggle_board[r][c], r, c) for r, c in row])

    print("The letters are:", letters)
    return letters

def get_words(boggle_board, word_list, value, max_word_length):
    """
    Function to retrieve words from the boggle-board
    :param boggle_board:
    :param word_list:
    :param value:
    :param max_word_length:
    :return:
    """
    # This is basically implementing the DFS logic
    def dfs_helper(words, value, visited, current_word=""):
        """
        :param words:
        :param value:
        :param visited:
        :param current_word:
        :return:
        """

        # Basic Sanity checks / Recurse conditions
        if len(current_word) > max_word_length: return
        if is_word_valid(current_word, word_list):
            words.add(current_word)

        visited.add(value)
        neighbours = get_neighbours(boggle_board, value[1], value[2])
        print("The neighbours are:", neighbours)

        neighbours = [c for c in neighbours if c not in visited]

        ncount = [len(get_prefix_match(current_word + n[0], word_list)) for n in neighbours]
        matches = zip(neighbours, ncount)
        for c, match in matches:
            if match > 0:
                dfs_helper(words, c, visited, current_word=current_word+c[0])

    words = set()
    dfs_helper(words, value, set(), current_word=value[0])
    return words



def boggle_solve(boggle_board, word_list, roots, max_word_length):
    words_found = set()
    for value in roots:
        result = get_words(boggle_board, word_list, value, max_word_length)
        words_found = words_found.union(result)
    return words_found


if __name__ == "__main__":

    # Creating an adjacency list for the dictionary
    word_list = get_word_list()
    print("The word_list is:", word_list)

    # Setting boundary conditions
    board_size = 3
    max_word_length = 100

    # Create a random grid to play the game of boggle
    boggle_board = create_boggle_board(board_size=board_size)
    boggle_board = [['d', 'z', 'x'],
                    ['e', 'a', 'i'],
                    ['q', 'u', 't']]
    display_boggle_board(boggle_board)

    roots = []
    for r, row in enumerate(boggle_board):
        for c, value in enumerate(row):
            roots.append((value, r, c))

    words_found = boggle_solve(boggle_board, word_list, roots, max_word_length)
    print("The word found are:", sorted(words_found))
    print("The number of words found are:", len(words_found))