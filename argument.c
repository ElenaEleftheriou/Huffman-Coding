#include "argument.h"

void allocateMem(char **filename, char *optarg)
{
    *filename = (char *)malloc((strlen(optarg) + 1) * sizeof(char));
    if (*filename == NULL)
    { // Check if memory allocation was successful
        perror("Memory allocation failed.\n");
        free(*filename);
        exit(EXIT_FAILURE);
    }
}

void readArg(int argumentc, char **argumentv)
{
    char *filename = NULL;
    char *filenameOut = NULL;
    char *prob = NULL;
    int c;
    opterr = 0;
    if (argumentc == 1)
    {
        printf("No command line arguments given!\n");
        exit(EXIT_FAILURE);
    }
    float *f = (float *)malloc(128 * sizeof(float));
    if (f == NULL)
    {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 128; i++)
        f[i] = 0.0;
    char **codes = (char **)malloc(129 * sizeof(char *));
    if (codes == NULL)
    {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 128; i++)
        codes[i] = NULL;
    int count = 0;
    TREENODE **t = (TREENODE **)malloc(128 * sizeof(TREENODE *));
    if (t == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    while ((c = getopt(argumentc, argumentv, "p:s:e:d:")) != -1)
    {
        switch (c)
        {
        case 'p':
            allocateMem(&filename, optarg);
            allocateMem(&filenameOut, optarg);
            strcpy(filename, optarg);
            if (optind < argumentc)
            {
                strcpy(filenameOut, argumentv[optind++]);
            }
            else
            {
                printf("Error: Missing output file after -p\n");
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            // Check if both input and output files are provided
            if (filename == NULL || filenameOut == NULL)
            {
                printf("No input file given!\n");
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            // Check if file names end with ".txt"
            if (strstr(filename, ".txt") == NULL || strstr(filenameOut, ".txt") == NULL)
            {
                printf("Error: File names must end with '.txt'\n");
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            probFile(filename, filenameOut, f);
            free(filename);
            free(filenameOut);
            break;
        case 's':
            allocateMem(&filename, optarg);
            strcpy(filename, optarg);
            if (filename == NULL)
            {
                printf("No input file given!\n");
                free(filename);
                exit(EXIT_FAILURE);
            }
            // Check if file names end with ".txt"
            if (strstr(filename, ".txt") == NULL)
            {
                printf("Error: File names must end with '.txt'\n");
                free(filename);
                exit(EXIT_FAILURE);
            }
            readProb(filename, f);
            count = huffmanT(f, codes, t);
            free(filename);
            break;
        case 'e':
        case 'd':
            allocateMem(&prob, optarg);
            strcpy(prob, optarg);
            allocateMem(&filename, optarg);
            allocateMem(&filenameOut, optarg);
            if (optind < argumentc)
            {
                strcpy(filename, argumentv[optind++]);
            }
            else
            {
                printf("Error: Missing output file after -%c\n", c);
                free(prob);
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            if (optind < argumentc)
            {
                strcpy(filenameOut, argumentv[optind++]);
            }
            else
            {
                printf("Error: Missing output file after -%c\n", c);
                free(prob);
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            // Check if both input and output files are provided
            if (filename == NULL || filenameOut == NULL || prob == NULL)
            {
                printf("No input file given!\n");
                free(prob);
                free(filename);
                free(filenameOut);
                exit(EXIT_FAILURE);
            }
            // Check if file names end with ".txt"
            if (c == 'e')
            {
                if (strstr(filename, ".txt") == NULL || strstr(filenameOut, ".txt.enc") == NULL || strstr(prob, ".txt") == NULL)
                {
                    printf("Error: File names must end with '.txt' and output file with '.enc'\n");
                    free(prob);
                    free(filename);
                    free(filenameOut);
                    exit(EXIT_FAILURE);
                }
            }
            else if (c == 'd')
            {
                if (strstr(filename, ".txt.enc") == NULL || strstr(filenameOut, ".txt.new") == NULL || strstr(prob, ".txt") == NULL)
                {
                    printf("Error: File names must end with '.txt', input file with '.enc' and output file with '.new'\n");
                    free(prob);
                    free(filename);
                    free(filenameOut);
                    exit(EXIT_FAILURE);
                }
            }
            readProb(prob, f);
            count = huffmanT(f, codes, t);
            if (c == 'e')
                printEncFile(codes, filename, filenameOut);
            else
                decompFile(filename, filenameOut, t, count);
            free(prob);
            free(filename);
            free(filenameOut);
            break;
        case '?':
            if (optopt == 'p')
                printf("Option requires an argument -- 'p'\n");
            if (optopt == 's')
                printf("Option requires an argument -- 's'\n");
            if (optopt == 'e')
                printf("Option requires an argument -- 'e'\n");
            if (optopt == 'd')
                printf("Option requires an argument -- 'd'\n");
            else if (isprint(optopt))
                fprintf(stderr, "Invalid option -- '%c'\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            exit(EXIT_FAILURE);
            break;
        }
    }
    // Free other dynamically allocated arrays
    for (int i = 0; i < 128; i++)
    {
        if (codes[i] != NULL)
        {
            free(codes[i]);
        }
    }
    free(codes);
    for (int i = 0; i < 128; i++)
    {
        if (t[i] != NULL)
        {
            freeTree(t[i]);
        }
    }
    free(f);
    free(t);
}

#ifdef DEBUG3
int main(int argc, char *argv[])
{
    readArg(argc, argv);
    return 0;
}
#endif