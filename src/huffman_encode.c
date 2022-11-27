/**
 * Huffman compress algorithm.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_format.h"
#include "huffman.h"


void debug_print_table(freTable_t *table, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        printf("id = %d, freq_val = %d, ch = %c, ascii val = %d \n", i, table[i].freq, table[i].ch, table[i].ch);
    }
}

/**
 * count characters frequence and store into a table
 * 
 * @param inputString   string to be encoded.
 * @param str_len       length of string, doesn't include '\0'.
 * @param table         frequence count table
 */
void initFreqTable(char *inputString, int str_len, freTable_t *table)
{
    int i;
    char this_ch;

    if (NULL == inputString) {
        return;
    }

    for (i = 0; i < str_len; i++) {
        this_ch = inputString[i];
        /* printf("tmp ascii = %d\n", this_ch); */
        table[this_ch].freq += 1;
        table[this_ch].ch = this_ch;
    }
}

/* Exchange two elements in table */
static void table_exchange(freTable_t *table, int index1, int index2)
{
    freTable_t temp;
    temp = table[index1];
    table[index1] = table[index2];
    table[index2] = temp;
}

static void bubbleSort(freTable_t *table, int len)
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

static void sortTable(freTable_t *table, int len_total)
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

    bubbleSort(table, left);
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
node_t *generateHuffmanTree(freTable_t *table)
{
    freTable_t *tb;
    node_t *root;
    node_t *lchild;
    node_t *rchild;

    if (table == NULL) {
        printf("table is NULL");
        return NULL;
    }

    sortTable(table, ASCII_NUM_TOTAL);
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

int huffmanEncode(char *string, int str_len)
{
    node_t *huffmanTree;
    freTable_t feq_table[ASCII_NUM_TOTAL];

    memset(feq_table, 0, sizeof(freTable_t) * ASCII_NUM_TOTAL);
    initFreqTable(string, str_len, feq_table);
    huffmanTree = generateHuffmanTree(feq_table);
    if (huffmanTree == NULL) {
        printf("wtf??\n");
        return EXE_ERROR;
    }

    return EXE_OK;
}
