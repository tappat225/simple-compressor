/**
 * Project:     simple-compressor
 * Author:      TappaT
 * URL:         https://github.com/tappat225/simple-compressor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "type_format.h"

/* Convert input file to string. */
char *get_file_content(const char *input_file_path)
{
    FILE *input_file;
    char *file_content;
    int content_length;

    input_file = fopen(input_file_path, "rb");
    if (NULL == input_file) {
        return NULL;
    }

    fseek(input_file, 0, SEEK_END);
    content_length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    file_content = (char*)malloc(content_length);
    if (file_content) {
        fread(file_content, 1, content_length, input_file);
    }

    fclose(input_file);

    return file_content;
}

int main(int argc, char *argv[])
{
    char test_string[] = "abbcccdd";
    int len = strlen(test_string);
    if (huffman_encode(test_string, len) == EXE_OK) {
        printf("ok!\n");
    }

    return 0;
}
