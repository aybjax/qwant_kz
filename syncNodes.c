#include "headers.h"

int syncNodes(GlobalNode* nodes)
{
    //get the newest and greatest node
    updateArr(nodes);
    
    if(nodes->syncd == NODES_SYNCD) return 1;
    //depricated
    //if(nodes->headBlock == NULL) return 1;

    reNewEachNodeBlock(nodes);
    reNewAdjArr(nodes);

    nodes->syncd = NODES_SYNCD;

    return 0;
}

int reNewAdjArr(GlobalNode* nodes)
{
    int id = nodes->heapNodes[0];
    int maxId = nodes->nextNodeId;
    id = nodes->nidById[id - nodes->idErr];
    Node* node = getNodeByNid(nodes, id);
    int bTime = node->timestamp;
    int blockNbr = node->blockNbr;

    for(int i=0; i<maxId; i++)
    {
        if(nodes->bNbrById[i] == INT_MIN) continue;
        nodes->bNbrById[i] = blockNbr;
        nodes->timeById[i] = bTime;
    }

    return 0;
}

int reNewEachNodeBlock(GlobalNode* nodes)
{
    if(nodes->nbrNodes == 0) return 1;

    //depricated
    //Block* headBlock = nodes->headBlock;
    //get the block to new against
    int id = nodes->heapNodes[0];
    id = nodes->nidById[id - nodes->idErr];
    Block* headBlock = getNodeByNid(nodes, id)->block;


    Node* node = nodes->headNode;

    //1st get ID from heap
    int blockNodeID = nodes->heapNodes[0];

    //check if the top node has any blocks
    if(nodes->bNbrById[blockNodeID] == 0) return 1;

    //get NID and then actual node
    int NID = nodes->nidById[blockNodeID];

    Node* blockNode = getNodeByNid(nodes, NID);
    
    while(node != NULL)
    {
        //sanity check
        if(blockNode->id != node->id)
        {    
            //node prop: metadata of blocks
            cpynodeMetaData(blockNode, node);

            deleteBlockChain(node->block);

            node->block = NULL;

            createBlockChain(node, headBlock);

        }

        node = node->nextNode;
    }

    return 0;
    
}

int createBlockChain(Node* node, Block* headBlock)
{
    node->block = malloc(sizeof(Block));

    copyBlock(node->block, headBlock);
}

int copyBlock(Block* emptyBlock, Block* infoBlock)
{
    for(register int i=0; i<bidLength; i++)
    {
        emptyBlock->bid[i] = infoBlock->bid[i];
    }
    emptyBlock->prevBlock = NULL;

    if(infoBlock->prevBlock == NULL) return 0;

    emptyBlock->prevBlock = malloc(sizeof(Block));

    copyBlock(emptyBlock->prevBlock, infoBlock->prevBlock);
}

int cpynodeMetaData(Node* blockNode, Node* node)
{
    node->blockNbr = blockNode->blockNbr;
    node->timestamp = blockNode->timestamp;
}

int deleteBlockChain(Block* block)
{
    Block* prev;
    while(block != NULL)
    {
        prev = block->prevBlock;
        free(block);
        block = prev;
    }
}


bool isSyncd(GlobalNode* nodes)
{
    int firstBlockNbr = -1;
    int firstTime = -1;

    for(register int i=0; i < nodes->nextNodeId; i++)
    {
        if(nodes->bNbrById[i] == INT_MIN) continue;
        if(firstBlockNbr == -1)
        {
            firstBlockNbr = nodes->bNbrById[i];
            firstTime = nodes->timeById[i];
            continue;
        }else
        {
            if(firstBlockNbr != nodes->bNbrById[i]) return false;
            /** even if all nodes have same block compositions,
            *       time of creation of outermost block matters **/
            if(firstTime != nodes->timeById[i]) return false;
        }
        
    }

    if(traverseAllBlocks(nodes) == false) return false;

    return true;
}

int setSyncd(GlobalNode* nodes)
{
    if(isSyncd(nodes) == true)
    {
        nodes->syncd = NODES_SYNCD;
        return 0;
    }
    nodes->syncd = NODES_NOT_SYNCD;
    return 1;
}

//assumes that all nodes have same nbr of blocks
bool traverseAllBlocks(GlobalNode* nodes)
{
    bool ret;
    int i = 0;
    int arrSize = nodes->nbrNodes;
    if (arrSize == 0) return true;
    Block** arrBlocks = malloc(sizeof(Block) * arrSize);
    Node* tmpNode = nodes->headNode;
    
    while( tmpNode != NULL)
    {
        arrBlocks[i++] = tmpNode->block;
        tmpNode = tmpNode->nextNode;
    }

    while(arrBlocks[0] != NULL)
    {
        for(i=1; i<arrSize; i++)
        {
            if(mine_strcmp(arrBlocks[i-1]->bid, arrBlocks[i]->bid) == -1) 
            {
                free(arrBlocks);
                goto traverseAllBlocks;
            }
            arrBlocks[i-1] = arrBlocks[i-1]->prevBlock;
        }
        //because i overflows (i is not less than arrSize)
        arrBlocks[i-1] = arrBlocks[i-1]->prevBlock;
    }

    free(arrBlocks);
    return true;
    traverseAllBlocks:
    return false;
}