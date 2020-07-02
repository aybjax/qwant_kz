#include "headers.h"

void freeNode(GlobalNode* nodes);
void freeBlock(Node* node);
    //int id = 0;
void freeThemAll( GlobalNode* nodes, int mode)
{
    if((mode & NODE_FREE) != 0)
    {
        //free node starting from beginning;
        freeNode(nodes);
        //printf("ids arr - %d\n", id++);
    }
    if((mode & NON_HASH) != 0)
    {
        //free nodes arrays - globalNode created before node if de novo creation
        free(nodes->heapNodes);
        //printf("ids arr - %d\n", id++);
        free(nodes->posMapNodesById);
        //printf("ids arr - %d\n", id++);
        free(nodes->nidById);
        //printf("ids arr - %d\n", id++);
        free(nodes->bNbrById);
        //printf("ids arr - %d\n", id++);
        free(nodes->timeById);
        //printf("ids arr - %d\n", id++);
    }
    if( (mode & HASH) != 0)
    {
        free(nodes->idByNid);
        //printf("ids arr - %d\n", id++);
    }
    if( (mode & NODE_FREE) != 0)
    {
        free(nodes);
        //printf("ids arr - %d\n", id++);
    }
}

void freeNode(GlobalNode* nodes)
{

    Node* prevNode = nodes->headNode;
    Node* nextNode;
    while( prevNode != NULL )
    {
        //printf("freeNOde address %p\n", prevNode);
        nextNode = prevNode->nextNode;
        freeBlock(prevNode);
        free(prevNode);
        prevNode = NULL;
        if (nextNode != NULL) prevNode = nextNode;
    }
}

void freeBlock(Node* node)
{
    static Block* freedPointersAddress[100];
    static int freePointersSize;
    Block* currBlock = node->block;
    Block* prevBlock;
    while( currBlock != NULL )
    {
        for(register int i=0; i<freePointersSize; i++)
        {
            //printf("%dth iteration\n", freePointersSize+1);
            if(freedPointersAddress[i] == currBlock) return;
        }
        prevBlock = currBlock->prevBlock;
        freedPointersAddress[freePointersSize++] = currBlock;
        free(currBlock);
        currBlock = NULL;
        if (prevBlock != NULL) currBlock = prevBlock;
    }
}