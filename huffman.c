/**
 * @file huffman.c
 * @brief Main program for Huffman coding operations.
 *
 * This program serves as the main entry point for a suite of programs
 * implementing Huffman coding functionalities. It utilizes the functionalities
 * defined in "argument.c" for command-line argument parsing, in "file.c" for file I/O and
 * in "huffmanTree.c" for Huffman coding and decoding.
 *
 * @see argument.h
 * @author Elena Eleftheriou
 */

#include "argument.h"

int main(int argc, char *argv[])
{
    readArg(argc, argv);
    return 0;
}