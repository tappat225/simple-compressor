
#ifndef _HOFFMAN_TREE_
#define _HOFFMAN_TREE_

typedef struct hoffman_tree_node
{
    struct hoffman_tree_node *lchild;
    struct hoffman_tree_node *rchild;
    int val;
} node_t;

/* free manually after used. */
node_t *create_node();

void destory_node(node_t **node_paddr);

#endif /* _HOFFMAN_TREE_ */
