#include "headers.h"

int reallocArr(GlobalNode* nodes)
{
    bool capChange = false;
    int span = nodes->nextNodeId - nodes->idErr;
    int cap = nodes->cap;

    //there are two variants
        //nbr of node is larger
        //nbr is smaller, but id is shifted
    /** add minimal and maximal saturation in reallocArr **/
    if( span > nodes->cap * ( 1- initSaturation ) )
    {
        capChange = true;
        if( /*cap > nodes->initCapacity &&*/ nodes->nbrNodes > nodes->cap / (1+initSaturation) )  nodes->cap *= 2;
    }
    else if(nodes->cap > nodes->initCapacity && nodes->nbrNodes < nodes->cap/( 5+initSaturation ) )
    {
        capChange = true;
        nodes->cap /= 2;
    }

    if( capChange == true )
    {//allocate new arrays
        int *heapNodes = nodes->heapNodes;
        int *posMap = nodes->posMapNodesById;
        int *nidById = nodes->nidById;
        int *blockNbr = nodes->bNbrById;
        int *time = nodes->timeById;

        int oldIdErr = nodes->idErr;
        int newShift=0;

        //get new idErr
        for(int i=nodes->idErr; i<nodes->cap; i++)
            if( nidById[i] != INT_MIN )
            {
                nodes->idErr = i + oldIdErr;
                newShift = i;
                break;
            }
        if(newShift == 0 && nodes->nbrNodes == 0) nodes->idErr = nodes->nextNodeId;

        nodes->heapNodes = malloc(nodes->cap * sizeof(int));
        nodes->posMapNodesById = malloc(nodes->cap * sizeof(int));
        nodes->nidById = malloc(nodes->cap * sizeof(int));
        nodes->bNbrById = malloc(nodes->cap * sizeof(int));
        nodes->timeById = malloc(nodes->cap * sizeof(int));
        /////////////directed
        initArr(nodes, NON_HASH);
        cap = cap < nodes->cap ? cap : nodes->cap;
        int register nextNodeId = nodes->nextNodeId;
        for(register int i= newShift; i<nextNodeId && i-newShift<cap; i++)
        {
            nodes->posMapNodesById[i-newShift] = posMap[i];
            nodes->nidById[i-newShift] = nidById[i];
            nodes->bNbrById[i-newShift] = blockNbr[i];
            nodes->timeById[i-newShift] = time[i];
        }
        //as heapNodes is  not array => do not skip 0 - idErr interval
        for(register int i=0; i<cap; i++)
            nodes->heapNodes[i] = heapNodes[i];
        free(heapNodes);
        free(posMap);
        free(nidById);
        free(blockNbr);
        free(time);
    }

    capChange = false;

    //deal with hash table
    /** add minimal and maximal saturation in reallocArr **/
    if(nodes->hashed > (1 - initSaturation) * nodes->hashSize)
    {
        capChange = true;
        if(nodes->nbrNodes > (1 - initSaturation) * nodes->hashSize) nodes->hashSize *=2;
    }
    else if( nodes->hashSize > nodes->initHash
            && nodes->nbrNodes < nodes->hashSize/( 5+initSaturation )) 
    {
        nodes->hashSize /= 2;
        capChange = true;
    }
    
    if( capChange == true )
    {
        
        nodes->hashed = 0;
        freeThemAll(nodes, HASH);
        nodes->idByNid = malloc(nodes->hashSize * sizeof(int));
        initArr(nodes, HASH);

        Node *node = nodes->headNode;

        while(node != NULL)
        {
            hashTput(nodes, node);
            node = node->nextNode;
        }
    }

    return 0;
}