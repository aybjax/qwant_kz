#include "headers.h"

int /*block* bolfan*/ createBlock(GlobalNode* nodes, int nid, int bid)
{
    //get the node
    Node* node;
    if(nid == INT_MAX)
    {
        node = nodes->headNode;
    }else if( !nidExists(nodes, nid) )
    {
        NODE_NO_EXIST;
        return 1;
    }
    else node = getNodeByNid(nodes, nid);
    
    printf("add block %d to node %d\n", bid, node->nid);
    
    while(node != NULL)
    {
        if( bidExists(node, bid) )
        {
            BLOCK_EXIST;
            if(nid == INT_MAX)
                goto skipTheBlockWhileLoop;
            else
                return 1;
        }
        Block* block = malloc(sizeof(Block));
        if ( block == NULL )
        {
            nodes->syncd = NODES_NOT_SYNCD;
            NO_RESOURCE;
            return -1;
        }

        nodes->bNbrById[node->id] = ++node->blockNbr;
        //get time in seconds
        nodes->timeById [node->id] = time(NULL);

        if(node->blockNbr == 1)
        {   //very first block
            block->prevBlock = NULL;
        }else
        {
            block->prevBlock = node->block;
        }
        //here and above - update blockchain of the node
        node->block = block;
        snprintf(block->bid, bidLength, "%d", bid);
        
        // if * is not given => only one node is updated
        if(nid != INT_MAX)
        {//then only one node is updated
            if(nodes->nbrNodes!=1)
            {//if the not the only one node
                nodes->syncd = NODES_NOT_SYNCD;
            }
            break;
        }
        else
        {
            skipTheBlockWhileLoop:
            node = node->nextNode;
        }
    }

    //depricated
    //nodes->headBlock = block;

    return 0;
}