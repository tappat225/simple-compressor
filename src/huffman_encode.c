/**
 * Huffman compress algorithm.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_format.h"
#include "huffman.h"

#define DEBUG_D
#ifdef  DEBUG_D
void debug_print_table(freq_table_t *table, int len)
{
    int i;

    printf("\n\t------------- DEBUG PRINT TABLE ---------------\n");
    for (i = 0; i < len; i++) {
        printf("id = %d, freq_val = %d, ch = %c, ascii val = %d \n", i,\
            table[i].freq, table[i].ch, table[i].ch);
    }
}

void print_tree_recur(node_t *node, char op[], int level) {
    if (node == NULL) {
        return;
    }

    printf("\n op: %s\n", op);
    printf("freq = %d, ch = %c, level = %d\n", node->freq_val, node->ch,\
        level);
    print_tree_recur(node->lchild, "left", level + 1);
    print_tree_recur(node->rchild, "right", level + 1);
}

void print_tree(node_t *root) {
    printf("\n\t------------- DEBUG PRINT TREE ---------------\n");
    print_tree_recur(root, "root", 0);
}

void print_mapping_table(map_table_t *t)
{
    map_table_t *tp;

    tp = t;
    printf("\n\t------------- DEBUG PRINT MAPPING TABLE ---------------\n");
    while (tp != NULL && tp->origin_ch >= 'a') {
        printf("origin = %c, compressed = %s\n", tp->origin_ch,\
            tp->compressed_bits);
        tp++;
    }
    
}

#endif

/**
 * count characters frequence and store into a table
 * 
 * @param input_string   string to be encoded.
 * @param str_len       length of string, doesn't include '\0'.
 * @param table         frequence count table
 */
void init_freq_table(char *input_string, int str_len, freq_table_t *table)
{
    int i, t_index;
    char this_ch;

    if (NULL == input_string) {
        return;
    }

    for (i = 0; i < str_len; i++) {
        this_ch = input_string[i];
        t_index = (int)this_ch;
        /* printf("tmp ascii = %d\n", this_ch); */
        table[t_index].freq += 1;
        table[t_index].ch = this_ch;
    }
}

/* Exchange two elements in table */
static void table_exchange(freq_table_t *table, int index1, int index2)
{
    freq_table_t temp;
    temp = table[index1];
    table[index1] = table[index2];
    table[index2] = temp;
}

static void bubble_sort(freq_table_t *table, int len)
{
    int i;

    while (--len) {
        for (i = 0; i < len; i++) {
            if (table[i].freq > table[i + 1].freq) {
                table_exchange(table, i, i + 1);
            }
        }
    }
}

static void sort_table(freq_table_t *table, int len_total)
{
    int left, right;

    if (table == NULL) {
        return;
    }

    /* make zeros to the tail, like {5, 3, 1, 8, 0, 0, ...} */
    left = 0;
    right = len_total - 1;      /* 127 */
    while (left != right) {
        if ((table[left].freq == 0) && (table[right].freq != 0)) {
            table_exchange(table, left, right);
        }

        left += (table[left].freq != 0)? 1 : 0;
        if (left == right) {
            break;
        }

        right += (table[right].freq == 0)? -1 : 0;
    }

    bubble_sort(table, left);
    /* 
     *  now the table frequence seqence should be
     * in format {1, 1, 2, 2, 3, 4, 0, 0, ...}
     */
}


/**
 * 
 * @param table     frequence table.
 * 
 */
node_t *generate_huffman_tree(freq_table_t *table, int *elem_num)
{
    freq_table_t *tb;
    node_t *root;
    node_t *root_stash;
    node_t *root_extra;     /* For two nodes with same freq situation. */
    node_t *node_one;
    node_t *node_two;

    if (table == NULL) {
        printf("table is NULL");
        return NULL;
    }

    sort_table(table, ASCII_NUM_TOTAL);
    if (table[0].freq == 0) {
        printf("first elem of table is 0\n");
        return NULL;
    }

#ifdef DEBUG_D
    // debug_print_table(table, ASCII_NUM_TOTAL);
#endif

    tb = table;
    root = create_node(tb->freq, 0);
    tb++;
    if ((tb == NULL) || (tb->freq == 0)) {
        pr_warning("Are you going to build huffman tree with only one "\
        "element?");
    }

    while ((NULL != tb) && (tb->freq != 0)) {
        node_one = create_node(tb->freq, tb->ch);
        /* Situation when two new elements have same value. */
        if (((tb + 1) != NULL) && (tb->freq == (tb + 1)->freq)) {
            node_two = create_node((tb + 1)->freq, (tb + 1)->ch);
            root_extra = create_node((tb->freq) * 2, 0);
            root_extra->lchild = node_one;
            root_extra->rchild = node_two;
            root_stash = root;
            root = create_node(0, 0);
            root->lchild = root_stash;
            root->rchild = root_extra;
            root->freq_val = root->lchild->freq_val + root->rchild->freq_val;
            tb += 2;
            *elem_num += 2;
            continue;
        }

        root_stash = root;
        root = create_node(0, 0);
        root->lchild = root_stash;
        root->rchild = node_one;
        root->freq_val = root->lchild->freq_val + root->rchild->freq_val;
        tb++;
        *elem_num += 1;
    }

    return root;
}

static void find_and_set_map_recus(node_t *node, map_table_t **tp_p, int deep)
{
    pr_debug("deep = %d", deep);
    if ((node->lchild == NULL) && (node->rchild == NULL)) {
        pr_debug("node->ch = %c", node->ch);
        (*tp_p)->origin_ch = node->ch;
        (*tp_p)->compressed_bits[deep] = '\0';
        (*tp_p)++;
        return;
    }

    if (node->rchild != NULL) {
        pr_debug("go right");
        (*tp_p)->compressed_bits[deep] = 1;
        find_and_set_map_recus(node->rchild, tp_p, deep + 1);
    }

    pr_debug("go left");
    (*tp_p)->compressed_bits[deep] = 0;
    find_and_set_map_recus(node->lchild, tp_p, deep + 1);
}

/**
 * 
 * @param root      root of huffman tree
 */
map_table_t *generate_mapping_table(node_t *root, int elem_num)
{
    map_table_t *new_table;
    map_table_t *tp;

    pr_debug("element number = %d", elem_num);
    new_table = (map_table_t*)malloc(sizeof(map_table_t) * elem_num);
    memset(new_table, 0, sizeof(map_table_t) * elem_num);
    tp = new_table;
    find_and_set_map_recus(root, &tp, 0);

    return new_table;
}

int huffman_encode(char *string, int str_len)
{
    node_t *huffman_tree;
    freq_table_t feq_table[ASCII_NUM_TOTAL];
    map_table_t *huffman_map_table;
    int elem_num = 0;

    memset(feq_table, 0, sizeof(freq_table_t) * ASCII_NUM_TOTAL);
    init_freq_table(string, str_len, feq_table);
    huffman_tree = generate_huffman_tree(feq_table, &elem_num);
    if (huffman_tree == NULL) {
        printf("wtf??\n");
        return EXE_ERROR;
    }

    huffman_map_table = generate_mapping_table(huffman_tree, elem_num);
    if (huffman_map_table == NULL) {
        pr_error("huffman table failed");
        return EXE_ERROR;
    }

    print_mapping_table(huffman_map_table);
    print_tree(huffman_tree);
    return EXE_OK;
}
