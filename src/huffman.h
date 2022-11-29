
#ifndef _HOFFMAN_TREE_
#define _HOFFMAN_TREE_


/* -------------------------- Tree ---------------------------- */



typedef struct hoffman_tree_node
{
    struct hoffman_tree_node *lchild;
    struct hoffman_tree_node *rchild;
    int freq_val;
    char ch;
} node_t;

/* free manually after used. */
node_t *create_node(int freq_val, char ch);

void destory_node(node_t **node_paddr);


/* ------------------------ Encode ---------------------------- */
int huffman_encode(char *string, int str_len);

/* ------------------------ Decode ---------------------------- */

#endif /* _HOFFMAN_TREE_ */
