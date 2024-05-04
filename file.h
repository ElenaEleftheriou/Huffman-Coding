/**
 * @file file.h
 * @brief A program for file manipulation and encoding.
 *
 * This program provides functions for reading files, processing data, and
 * encoding files based on a provided code. It includes functions to read
 * character occurrences, read probabilities, print arrays of floats and
 * arrays of strings, and encode files using a specified code.
 *
 * @note This program includes a debug mode, which is activated when the
 * preprocessor macro DEBUG1 is defined. In debug mode, a sample scenario
 * is provided in the main function for testing the file reading and printing
 * functionalities.
 *
 * @author Elena Eleftheriou
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef FILEH
#define FILEH

/**
 * @brief Reads characters from a file and updates the frequency array.
 *
 * This function reads characters from the specified file and updates the frequency
 * array accordingly. It returns the total number of characters read.
 *
 * @param filename input file.
 * @param f The frequency array.
 * @return The total number of characters read.
 */
int readFile(char *, float *);

/**
 * @brief Reads probabilities from a file and updates the frequency array.
 *
 * This function reads probabilities from the specified file and updates the
 * frequency array accordingly.
 *
 * @param filename input file.
 * @param f The frequency array.
 * @return void
 */
void readProb(char *, float *);

/**
 * @brief Writes the frequency to a file.
 *
 * This function writes an the frequency to the specified output file.
 *
 * @param f The array of floats to be written.
 * @param output The name of the output file.
 * @param size The size of the array.
 * @return void
 */
void printF(float *, char *, int);

/**
 * @brief Writes the code of each character to a file.
 *
 * This function writes the codes of each character found from the tree, using
 * the frequencies, to the sspecified output file.
 *
 * @param code array of strings.
 * @param output output file.
 * @param size size of the array.
 * @return void
 */
void printFCode(char **, char *, int);

/**
 * @brief Reads an input file, encodes it using a code table, and writes to an output file.
 *
 * This function reads characters from the input file, encodes them using the provided
 * code table, and writes the encoded data to the output file.
 *
 * @param code code table.
 * @param input input file.
 * @param output output file.
 * @return void
 */
void printEncFile(char **, char *, char *);

#endif