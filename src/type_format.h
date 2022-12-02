#ifndef _TYPE_FORMAT_H_
#define _TYPE_FORMAT_H_

/**
 * =======================================================================
 * ===================              MACRO             ====================
 * =======================================================================
 */

/**
 *  For example, if you want to get binary format '0100', then use BIT_N(2),
 * which equals to (0x01 << 2).
 */
#define BIT_N(n)    (0x01 << n)

/* Character number in standard ascii table. */
#define ASCII_NUM_TOTAL 128

/* max length of bit stream 010001... */
#define MAX_BIT_LEN 128

/* return state */
#define EXE_OK      0
#define EXE_ERROR   -1

/* Helper functions */
#define pr_debug(fmt, ...)      \
    fprintf(stdout, "DEBUG INFO (function \"%s\" at line %d) :\n\t"fmt"\n",\
    __func__, __LINE__, ##__VA_ARGS__)

#define pr_warning(fmt, ...)      \
    fprintf(stdout, "WARNING (function \"%s\" at line %d) :\n\t"fmt"\n",\
    __func__, __LINE__, ##__VA_ARGS__)

#define pr_error(fmt, ...)      \
    fprintf(stdout, "ERROR (function \"%s\" at line %d) :\n\t"fmt"\n",\
    __func__, __LINE__, ##__VA_ARGS__)

/**
 * =======================================================================
 * =================              TYPEDEF             ====================
 * =======================================================================
 */

typedef unsigned char   u8;
typedef unsigned int    u32;

typedef struct freqenceCounterTable {
    u32 freq;
    char ch;
} freq_table_t;

typedef struct huffmanMappingTable {
    char origin_ch;
    char compressed_bits[MAX_BIT_LEN];
} map_table_t;

#endif /*_TYPE_FORMAT_H_*/
