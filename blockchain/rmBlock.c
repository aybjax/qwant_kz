#include "headers.h"

int rmBlock(GlobalNode* nodes, int bid)
{
    Node* node = nodes->headNode;

    while(node != NULL)
    {
        deleteBlock(node, bid);
        node = node->nextNode;
    }
    //depricated
    //nodes->headBlock=NULL;

    return 0;
}

int deleteBlock(Node* node, int bid)
{
    if( !bidExists(node, bid) )
    {
        BLOCK_NO_EXIST;
        return -1;
    }
    int bidNow;
    //next->prev is curr
    Block* next=NULL;
    Block* curr=node->block;
    while(curr!=NULL)
    {
        bidNow = interval_atoi(curr->bid, 0, STRINGLEN);
        if(bidNow == bid)
        {
            if(next == NULL)
            {//very first block is what we are looking for
                node->block = curr->prevBlock;
            }else
            {
                next->prevBlock=curr->prevBlock;
            }
            free(curr);
            break;
        }

        next=curr;
        curr=curr->prevBlock;
    }
    return 0;
}