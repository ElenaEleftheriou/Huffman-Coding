#include "huffmanTree.h"

void probFile(char *filename, char *filenameOut, float *f)
{
    int count = readFile(filename, f);
    if (count == -1)
    {
        printf("Error reading file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 128; i++)
        f[i] = f[i] / count;
    printF(f, filenameOut, 128);
}

TREENODE *createNode(float data, int c, TREENODE *l, TREENODE *r)
{
    TREENODE *t = (TREENODE *)malloc(sizeof(TREENODE));
    if (t == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    t->left = l;
    t->right = r;
    t->data = data;
    t->c = c;
    return t;
}

int findCount(float *f)
{
    int count = 0;
    for (int i = 0; i < 128; i++)
        if (f[i] > 0.0)
            count++;
    return count;
}

int huffmanT(float *f, char **codes, TREENODE **t)
{
    for (int i = 0; i < 128; i++)
        *(t + i) = createNode(f[i], i, NULL, NULL);
    int count = findCount(f);
    createTree(&count, t);
    for (int i = 0; i < 128; i++)
    {
        if (t[i] != NULL && t[i]->data > 0.0)
            count = i;
    }
    int *arr = (int *)malloc(128 * sizeof(int));
    createArray(t[count], arr, 0, codes);
    free(arr);
    // print codes
    for (int i = 32; i < 127; i++)
    {
        printf("%c :", (char)i);
        if (codes[i] == NULL)
            printf("No code\n");
        else
            printf("%s\n", codes[i]);
    }
    printFCode(codes, "codes.txt", 128);
    return count;
}

void findMin(TREENODE **t, int *c1, int *c2, int count)
{
    float min1 = 1, min2 = 1;
    for (int i = 0; i < 128; i++)
    {
        if (t[i] != NULL)
            if (t[i]->data > 0.0)
            {
                if (t[i]->data < min1)
                {
                    min2 = min1;
                    min1 = t[i]->data;
                    *c2 = *c1;
                    *c1 = i;
                }
                else if (t[i]->data < min2 && t[i]->data >= min1)
                {
                    min2 = t[i]->data;
                    *c2 = i;
                }
            }
    }
}

void createTree(int *count, TREENODE **t)
{
    if (*count == 1)
        return;
    int min1, min2;
    findMin(t, &min1, &min2, *count);
    TREENODE *tempt = createNode(t[min1]->data + t[min2]->data, -1, t[min1], t[min2]);
    removeNode(min1, min2, t, tempt);
    (*count)--;
    createTree(count, t);
}

void createArray(TREENODE *t, int arr[], int top, char **codes)
{
    if (t->left)
    {
        arr[top] = 0;
        createArray(t->left, arr, top + 1, codes);
    }
    if (t->right)
    {
        arr[top] = 1;
        createArray(t->right, arr, top + 1, codes);
    }

    if (!(t->left) && !(t->right))
    {
        if ((t->c) >= 0 && (t->c <= 127))
        {
            // Allocate memory for the code
            codes[t->c] = (char *)malloc((top + 1) * sizeof(char));
            if (codes[t->c] == NULL)
            {
                perror("Memory allocation failed!\n");
                exit(EXIT_FAILURE);
            }

            // Store the code in the array
            for (int i = 0; i < top; i++)
            {
                codes[t->c][i] = (char)(arr[i] + '0');
            }
            codes[t->c][top] = '\0'; // Null-terminate the string
        }
    }
}

void removeNode(int min1, int min2, TREENODE **t, TREENODE *temp)
{
    t[min1] = temp;
    t[min2] = NULL;
}

void decompFile(char *input, char *output, TREENODE **t, int i)
{
    FILE *fp1 = fopen(input, "r");
    if (fp1 == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    FILE *fp2 = fopen(output, "w");
    if (fp2 == NULL)
    {
        perror("Error opening output file");
        fclose(fp1);
        exit(EXIT_FAILURE);
    }
    int temp = 0;
    TREENODE *current = t[i];
    while ((temp = fgetc(fp1)) != EOF)
    {
        if (temp == '0')
            current = current->left;
        else
            current = current->right;
        if (current->c != -1)
        {
            fprintf(fp2, "%c", current->c);
            current = t[i];
        }
    }
    fclose(fp1);
    fclose(fp2);
}

void freeTree(TREENODE *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

#ifdef DEBUG2
int main()
{
    TREENODE **t = (TREENODE **)malloc(128 * sizeof(TREENODE *));
    if (t == NULL)
    {
        perror("Memory allocation failed");
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
    probFile("sample.txt", "probfile.txt", f);

    char **c = (char **)malloc(129 * sizeof(char *));
    if (c == NULL)
    {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 128; i++)
    {
        c[i] = NULL;
    }

    int count = huffmanT(f, c, t);
    printf("\n");
    decompFile("data.txt.enc", "data.txt.new", t, count);
    // Free the allocated memory for the tree
    for (int i = 0; i < 128; i++)
    {
        if (c[i] != NULL)
        {
            free(c[i]);
        }
    }
    free(c);
    for (int i = 0; i < 128; i++)
    {
        if (t[i] != NULL)
        {
            freeTree(t[i]);
        }
    }
    // Free other dynamically allocated arrays
    free(f);
    free(t);
    return 0;
}
#endif