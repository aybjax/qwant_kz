#include "headers.h"

int initBlockChain( GlobalNode* nodes, int nbrOfNodes, Node* node, Block* block )
{
    int ret=0;

    {   //block scope to get rid of variables
        int capSize;
        int calcSize = nbrOfNodes / initSaturation;
        capSize = initCap > calcSize ? initCap : calcSize;
        nodes->cap = capSize;
        nodes->initCapacity = capSize;
        //hashSize always needs to be power of 2
        nodes->hashSize = mostSignBit(capSize/initSaturation);
        nodes->initHash = nodes->hashSize;

        //nodes->adjCap = capSize;
        //nodes->leaveCap = calcSize;
        //nodes->blockHashSize = mostSignBit(capSize/initSaturation);

    }

    /*
    init properties of adjunct data structures
    */

    //create 5 arrays, which are indexed
        //by unique/incremental id of nodes
    nodes->heapNodes = malloc(nodes->cap * sizeof(int));
    nodes->posMapNodesById = malloc(nodes->cap * sizeof(int));
    nodes->nidById = malloc(nodes->cap * sizeof(int));
    nodes->bNbrById = malloc(nodes->cap * sizeof(int));
    nodes->timeById = malloc(nodes->cap * sizeof(int));

    //creat hash table
    nodes->idByNid = malloc(nodes->hashSize * sizeof(int));

    ////create block management arrays
    //nodes->tailByBidHash = malloc(nodes->blockHashSize * sizeof(int));
    //nodes->leaves = malloc(nodes->leaveCap * sizeof(int));
    //nodes->adjBlocks = malloc(nodes->adjCap * sizeof(int*));


    //initialize all array members to least possible integer
    initArr(nodes, ALL);

    /*
    initialize properties of nodes
    */
    //de novo creation
    //baseline data
    nodes->idErr = 0;
    nodes->nextNodeId = 0;
    nodes->syncd = NODES_SYNCD;
    nodes-> nbrNodes = nbrOfNodes;
    nodes->hashed = 0;
    /******************/
    nodes->headNode = NULL;
    nodes->tailNode = NULL;
    //depricated
    //nodes->headBlock = NULL;
    
    
    if (nbrOfNodes > 0)
    {   //if retrieving from saved file

        for(int i = 0; i < nbrOfNodes; i++, nodes->nextNodeId++)
        {
            ret = initNode(nodes, node+i);
            if ( ret != 0 )
            {
                printf("error msg");
                nodes->nbrNodes = i;
                nodes->syncd = NODES_NOT_SYNCD;
                break;
            }
            //adding blockChain possible only if nodes were initialized
            if ( block != NULL )
            {
                ret = initBlock(node+i, block);
                if ( ret != 0 )
                {
                    nodes->syncd = NODES_NOT_SYNCD;
                }
            }
        }
        
    }


    return 0;
}