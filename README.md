# Huffman

## Overview

This Huffman Coding program is a suite of functionalities for file manipulation and encoding. It includes modules for reading files, processing data, and performing Huffman encoding and decoding. The program is designed to work with ASCII text files containing characters in the range [0, 128].

## Modules

`huffman.c`

This is where the main entry point of the program.

`file.c`

This module provides functions for reading files, calculating character occurrences, and printing results. It is used for basic file I/O operations.

`argument.c`

The `argument.c` module handles command-line argument parsing. It defines options for encoding, decoding, and generating Huffman codes based on input files and probabilities.

`huffmanTree.c`

The `huffmanTree.c` module implements Huffman coding functionalities. It includes functions for calculating probabilities, creating Huffman trees, and encoding/decoding files.

## Usage

To compile the program, use the provided Makefile and then write, for example ./huffman -s probfile.txt