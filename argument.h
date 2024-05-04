/**
 * @file argument.h
 * @brief Program for file manipulation, encoding and decoding using Huffman coding.
 *
 * This program provides functionality for reading files, processing data,
 * and performing Huffman encoding and decoding. It supports the following
 * command-line options:
 *
 * - `-p`: Find the probabilities from a given file.
 * - `-s`: Generate Huffman codes and build a Huffman tree based on probabilities
 *         provided in a file.
 * - `-e`: Encode a file using a pre-built Huffman tree and save the result to another file.
 * - `-d`: Decode a Huffman-encoded file using a pre-built Huffman tree and save
 *         the result to another file.
 *
 * The program dynamically allocates memory for file names, probabilities, and
 * other data structures. It checks for memory allocation errors and ensures
 * that the provided file names have the required extensions. The program uses
 * a debug mode (activated by defining DEBUG3) for testing the argument parsing
 * and processing functionality.
 *
 * @note This program assumes that the provided input and output file names end
 * with ".txt", ".txt.enc", or ".txt.new" based on the operation being performed.
 * 
 * @see huffmanTree.h
 * @see file.h
 *
 * @author Elena Eleftheriou
 */

#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "huffmanTree.h"
#include "file.h"

#ifndef ARGUMENTH
#define ARGUMENTH

/**
 * @brief Allocates memory for a string and assigns the value of optarg to it.
 *
 * This function allocates memory for a string and assigns the value of optarg to it.
 * If memory allocation fails, the program exits with an error message.
 *
 * @param filename Pointer to a char pointer that will store the allocated memory.
 * @param optarg The value to assign to the allocated memory.
 * @return void
 */
void allocateMem(char **, char *);

/**
 * @brief Processes command line arguments and performs corresponding actions.
 *
 * This function processes the command line arguments using getopt.
 * It performs actions based on the specified options ('p', 's', 'e', 'd').
 * Handles memory allocation, file name validation, and other checks.
 *
 * @param argumentc Number of command line arguments.
 * @param argumentv Array of command line argument strings.
 * @return void
 */
void readArg(int, char **);

#endif