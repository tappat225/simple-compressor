/**
 * Hoffman compress algorithm.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_format.h"
#include "hoffman_tree.h"

#define ASCII_NUM_TOTAL 256

typedef unsigned int    table_t;

static table_t test_table[256] = {9, 8, 0, 5, 4};

/* count character freq and store into a table */
table_t *chCounter(char *p)
{
    table_t *table;
    char *tmp;

    if (NULL == p) {
        return NULL;
    }

    table = (table_t*)malloc(sizeof(table_t) * ASCII_NUM_TOTAL);
    memset(table, 0, ASCII_NUM_TOTAL);
    tmp = p;
    while (tmp != NULL) {
        table[(int)tmp] += 1;
        tmp++;
    }

    return table;
}

/* Convert input file to string. */
char *getFileContent(const char *inputFilePath)
{
    FILE *inputFile;
    char *fileContent;
    int contentLength;

    inputFile = fopen(inputFilePath, "rb");
    if (NULL == inputFile) {
        return NULL;
    }

    fseek(inputFile, 0, SEEK_END);
    contentLength = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    fileContent = (char*)malloc(contentLength);
    if (fileContent) {
        fread(fileContent, 1, contentLength, inputFile);
    }

    fclose(inputFile);

    return fileContent;
}

int main()
{
    const char inputFilePath[] = "./testfile.txt";
    // table_t *wordsCountTable;
    char *content;
    int contentLength;
    int i;

    content = getFileContent(inputFilePath);
    contentLength = strlen(content);
    
    return 0;
}
