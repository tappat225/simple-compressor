/**
 * File: tree_op.c
 * Description: basic operations for binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

node_t *create_node(int freq_val, char ch)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("error: malloc failed.");
        return NULL;
    }

    new_node->lchild = NULL;
    new_node->rchild = NULL;
    new_node->freq_val = freq_val;
    new_node->ch = ch;
    return new_node;
}

void destory_node(node_t **node_paddr)
{
    node_t *this_node = *node_paddr;
    if (NULL == this_node) {
        printf("warning: free an empty node.");
        return;
    }

    free(this_node);
    this_node = NULL;
}

void destory_tree(node_t *root)
{
    
}

void destroyHuffmanTree(node_t **root)
{
    
}
