#include "headers.h"

int initArr(GlobalNode* nodes, int allOrOnlyNonHash)
{
    int i=0;

    //fill the arrays with minimal possible integer
    
    if((allOrOnlyNonHash & NON_HASH) != 0)
        for(i=0; i < nodes->cap; i++)
        {
            nodes->heapNodes[i] = INT_MIN;
            nodes->posMapNodesById[i] = INT_MIN;
            nodes->nidById[i] = INT_MIN;
            nodes->bNbrById[i] = INT_MIN;
            nodes->timeById[i] = INT_MIN;

            ////at the beginning of cap == leaves/adj
            //nodes->leaves[i] = INT_MIN;
            //nodes->adjBlocks[i] = NULL;
        }

    if((allOrOnlyNonHash & HASH) == 0) return 0;
    for(i=0; i<nodes->hashSize; i++)
    {
        //blocks hash
        // nodes->tailByBidHash[i] = INT_MIN;
        // nodes->bidHashbybid[i] = INT_MIN;
        nodes->idByNid[i] = INT_MIN;
    }

    return 0;
}