#include <stdio.h>

int main()
{
    char c = 0;
    c = (0x01 << 6) | (0x01 << 0);
    printf("%c\n", c);
    return 0;
}
