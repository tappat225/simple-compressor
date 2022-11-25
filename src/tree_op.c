
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hoffman_tree.h"

node_t *create_node(int val)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    new_node->val = val;
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
