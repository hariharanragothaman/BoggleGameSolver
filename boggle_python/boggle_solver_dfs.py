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
    def helper(words, value, ignore, current_word=""):
        pass




    words = set()
    helper(words, value, set(), current_word=value[0])
    return words



def boggle_solve(boggle_board, word_list, roots, max_word_length):
    words_found = []
    for value in roots:
        result = get_words(boggle_board, word_list, value, max_word_length)
        words_found.append((result))
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
    display_boggle_board(boggle_board)

    words_found = boggle_solve(boggle_board, word_list, roots, max_word_length)
    print("The word found are:", set(words_found))
    print("The number of words found are:", len(set(words_found)))
