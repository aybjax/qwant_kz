#include "headers.h"

int reallocArr(GlobalNode* nodes)
{
    bool capChange = false;
    int span = nodes->nextNodeId - nodes->idErr;
    int nbr = nodes->nbrNodes;
    int cap = nodes->cap;
    int initCapacity = nodes->initCapacity;

    //there are two variants
        //nbr of node is larger
        //nbr is smaller, but id is shifted
    if( span > cap * ( 1- initSaturation ) )
    {
        capChange = true;
        if( /*cap > nodes->initCapacity &&*/ nbr > cap / (1+initSaturation) )  nodes->cap = cap*2;
    }
    else if(nbr > nodes->initCapacity && nbr < cap/( 2+initSaturation ) )
    {
        capChange = true;
        nodes->cap = cap/2;
    }

    if( capChange )
    {//allocate new arrays
        int *heapNodes = nodes->heapNodes;
        int *posMap = nodes->posMapNodesById;
        int *nidById = nodes->nidById;
        int *blockNbr = nodes->bNbrById;
        int *time = nodes->timeById;

        //get new idErr
        for(int i=nodes->idErr; i<nodes->cap; i++)
            if( nidById[i] != INT_MIN )
            {
                nodes->idErr = i;
                break;
            }
        


        nodes->heapNodes = malloc(nodes->cap * sizeof(int));
        nodes->posMapNodesById = malloc(nodes->cap * sizeof(int));
        nodes->nidById = malloc(nodes->cap * sizeof(int));
        nodes->bNbrById = malloc(nodes->cap * sizeof(int));
        nodes->timeById = malloc(nodes->cap * sizeof(int));
        /////////////directed
        initArr(nodes, NON_HASH);
        cap = cap < nodes->cap ? cap : nodes->cap;
        int register idErr = nodes->idErr;
        for(register int i=0 + nodes->idErr; i<cap; i++)
        {
            //heapNodes index is not id
            nodes->heapNodes[i-idErr] = heapNodes[i-idErr];
            nodes->posMapNodesById[i-idErr] = posMap[i];
            nodes->nidById[i-idErr] = nidById[i];
            nodes->bNbrById[i-idErr] = blockNbr[i];
            nodes->timeById[i-idErr] = time[i];
        }
        //as heapNodes is  not array => do not skip 0 - idErr interval
        for(register int i=0; i<idErr; i++)
            nodes->heapNodes[i] = heapNodes[i];
        free(heapNodes);
        free(posMap);
        free(nidById);
        free(blockNbr);
        free(time);
    }

    capChange = false;

    //deal with hash table
    if(nodes->hashed > 0.75 * nodes->hashSize) capChange = true;
    else if( nodes->hashSize > nodes->initHash
            && nodes->hashed < nodes->hashSize*0.25)
        
    
    if( capChange )
    {
        nodes->hashSize *= 2;
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