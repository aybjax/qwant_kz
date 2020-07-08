#include "headers.h"

int mostSignBit(int size)
{
    int ret = 1;

    size >>= 1;
    while(size>0)
    {
        size >>= 1;
        ret <<= 1;
    }
    return ret;
}