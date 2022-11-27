
#ifndef _TYPE_FORMAT_H_
#define _TYPE_FORMAT_H_

/**
 *  For example, if you want to get binary format '0100', then use BIT_N(2),
 * which equals to (0x01 << 2).
 */
#define BIT_N(n)    (0x01 << n)

/* Character number in standard ascii table. */
#define ASCII_NUM_TOTAL 128

#define EXE_OK      0
#define EXE_ERROR   -1

typedef unsigned char   u8;
typedef unsigned int    u32;

typedef struct freqenceCounterTable {
    u32 freq;
    char ch;
} freTable_t;

#endif /*_TYPE_FORMAT_H_*/
