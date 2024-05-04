/**
 * @file huffmanTree.h
 * @brief Implementation of Huffman coding functionalities.
 *
 * This file provides functions for Huffman coding, including probability
 * calculation, Huffman tree creation, file encoding, and decoding. It defines
 * structures and functions necessary for constructing and manipulating Huffman
 * trees. The code includes a debug mode (activated by defining DEBUG2) that
 * demonstrates the usage of the Huffman coding functions on a sample input.
 *
 * @see file.h
 * 
 * @author Elena Eleftheriou
 */

#include <math.h>
#include "file.h"

#ifndef HUFFMANH
#define HUFFMANH

/**
 * @struct TREENODE
 * @brief Structure representing a node in the Huffman tree.
 */
typedef struct TreeNode
{
    int c;                  /**< Character */
    float data;             /**< Frequency or data associated with the node */
    struct TreeNode *left;  /**< Pointer to the left child node */
    struct TreeNode *right; /**< Pointer to the right child node */
} TREENODE;

/**
 * @brief Creates a Huffman tree.
 *
 * Using recursion, this function creates a binary tree for the nodes that
 * were created before.
 *
 * @param count Pointer to the count of nodes.
 * @param t Pointer to an array of TreeNode pointers.
 * @return void
 */
void createTree(int *, TREENODE **);

/**
 * @brief Finds the indices of the two nodes with the minimum data.
 *
 * Given a lot of nodes, this function finds the 2 minimum frequencies of
 * 2 nodes and returns the index of the first one.
 *
 * @param t Array of TreeNode pointers.
 * @param c1 Pointer to store the index of the first minimum node.
 * @param c2 Pointer to store the index of the second minimum node.
 * @param count Number of nodes in the array.
 * @return void.
 */
void findMin(TREENODE **, int *, int *, int);

/**
 * @brief Generates a Huffman tree based on the given frequencies.
 *
 * This function firstly, creates nodes for all the characters in a file,
 * and then using createTree it creates a binary tree for the characters.
 * Then it stores in an array code the code of each character using the tree.
 * Lastly, it prints the codes.
 *
 * @param f Array of frequencies.
 * @param codes Array to store Huffman codes.
 * @param t Array of TreeNode pointers.
 * @return Index of the root node in the array.
 */
int huffmanT(float *, char **, TREENODE **);

/**
 * @brief Creates a new TreeNode.
 *
 * This function creates a new treenode pointer for the given data.
 *
 * @param data Frequency of the node.
 * @param c Character.
 * @param l Pointer to the left child node.
 * @param r Pointer to the right child node.
 * @return Pointer to the newly created TreeNode.
 */
TREENODE *createNode(float, int, TREENODE *, TREENODE *);

/**
 * @brief Reads the frequencies from a file and generates a probability file.
 *
 * Reads the frequencies from a given file, generates the probability and
 * prints it to a new file.
 *
 * @param filename Input file.
 * @param filenameOut Output file.
 * @param f Array to store frequencies.
 * @return void
 */
void probFile(char *, char *, float *);

/**
 * @brief Finds the count of non-zero frequencies.
 *
 * If a frequency wasn't 0, then the character was in the given text
 * and so it adds one to the count.
 *
 * @param f Array of frequencies.
 * @return Count.
 */
int findCount(float *);

/**
 * @brief Removes two nodes and inserts a new one in the array.
 *
 * This function, puts the new given node(temp) in the tree(t) in the
 * first position and then removes the node in the second position(because
 * the new node was made from the first and the second one).
 *
 * @param min1 Index of the first node to be removed.
 * @param min2 Index of the second node to be removed.
 * @param t Array of TreeNode pointers.
 * @param temp Pointer to the new TreeNode to be inserted.
 */
void removeNode(int, int, TREENODE **, TREENODE *);

/**
 * @brief Recursively generates Huffman codes for each leaf node in a binary tree.
 *
 * This function traverses a binary tree in a depth-first manner and generates
 * Huffman codes for each leaf node. The Huffman codes are stored in the 'codes'
 * array, where each index represents a character and its corresponding value is
 * the Huffman code as a dynamically allocated string.
 *
 * @param t Pointer to the current node in the binary tree.
 * @param arr Array to store the path to the current node.
 * @param top Current index in the 'arr' array.
 * @param codes Array to store Huffman codes for each leaf node.
 * @return void
 */
void createArray(TREENODE *, int[], int, char **);

/**
 * @brief Decompresses a file based on the Huffman tree.
 *
 * From a given file that consists of 0 and 1, it goes through the
 * tree until it finds a character with the same code and then it starts from the
 * top of the tree with the next code.
 *
 * @param input Compressed input file name.
 * @param output Decompressed output file name.
 * @param t Huffman tree.
 * @param i Index of the root node in the array.
 */
void decompFile(char *, char *, TREENODE **, int);

/**
 * @brief Recursively frees the memory allocated for a binary tree.
 *
 * This function recursively traverses a binary tree starting from the given node
 * and frees the memory allocated for each node in the tree. It uses a post-order
 * traversal to ensure that child nodes are freed before their parent nodes.
 *
 * @param node Pointer to the root node of the binary tree to be freed.
 * @return void
 */
void freeTree(TREENODE *);

#endif