/**
 * Huffman compress algorithm.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_format.h"
#include "huffman.h"

void debug_print_table(freq_table_t *table, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        printf("id = %d, freq_val = %d, ch = %c, ascii val = %d \n", i, table[i].freq, table[i].ch, table[i].ch);
    }
}

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
node_t *generate_huffman_tree(freq_table_t *table)
{
    freq_table_t *tb;
    node_t *root;
    node_t *lchild;
    node_t *rchild;

    if (table == NULL) {
        printf("table is NULL");
        return NULL;
    }

    sort_table(table, ASCII_NUM_TOTAL);
    if (table[0].freq == 0) {
        printf("first elem of table is 0\n");
        return NULL;
    }

    root = NULL;
    tb = table;
    while ((NULL != tb) && (tb->freq != 0)) {
        lchild = create_node(tb->freq, tb->ch);
        root = lchild;
        printf("root->freq_val = %d, root->ch = %c\n", root->freq_val, root->ch);
        if (NULL == ++tb) {
            break;
        }

        /* TODO: optimize case when two series elem with same freq_val. */
        rchild = create_node(tb->freq, tb->ch);
        root = create_node((lchild->freq_val + rchild->freq_val), 0);
        root->lchild = lchild;
        root->rchild = rchild;
        tb++;
    }

    return root;
}

/**
 * 
 * @param root      root of huffman tree
 */
map_table_t *generate_mapping_table(node_t *root, int elem_num)
{

}

int huffman_encode(char *string, int str_len)
{
    node_t *huffman_tree;
    freq_table_t feq_table[ASCII_NUM_TOTAL];

    memset(feq_table, 0, sizeof(freq_table_t) * ASCII_NUM_TOTAL);
    init_freq_table(string, str_len, feq_table);
    huffman_tree = generate_huffman_tree(feq_table);
    if (huffman_tree == NULL) {
        printf("wtf??\n");
        return EXE_ERROR;
    }

    return EXE_OK;
}
