/**
 * Project:     simple-compressor
 * Author:      TappaT
 * URL:         https://github.com/tappat225/simple-compressor
 */

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "type_format.h"

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

int main(int argc, char *argv[])
{
    char test_string[] = "ccdabbs sdda";
    if (huffmanEncode(test_string, 12) == EXE_OK) {
        printf("ok!\n");
    }

    return 0;
}
