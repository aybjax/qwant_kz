#include "headers.h"

bool bidExists(Node* node, int bidInt)
{
    char* blockBid;
    char bid[STRINGLEN];
    int ret = snprintf(bid, STRINGLEN, "%d", bidInt);
    Block* block = node->block;
    while(block!= NULL)
    {
        blockBid = block->bid;
        if( mine_strcmp(blockBid, bid)==0 )
            return true;
        else
            block = block->prevBlock;
    }
    return false;
}

int mine_strcmp(char* s1, char* s2)
{
    register int i, ret;
    register bool end = false;
    for(i=0; end!=true; i++)
    {
        ret = s1[i]-s2[i];
        if(ret != 0) return -1;
        if(s1[i] == 0 || s2[i] == 0) end = true;
    }
    return 0;
}