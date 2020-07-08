#include "headers.h"


char* resizeBuffer(char* buffer, int buffPointer, int* buffSize);

int listNodes(GlobalNode* nodes)
{
    char* buffer;
    int buffSize = BUFFSIZE;
    int buffPointer = 0;
    buffer = malloc(buffSize * sizeof(char));
    if(buffer == NULL)
    {
        NO_RESOURCE;
        return -1;
    }

    //code borrowed from printNodes.c
    Node* node = nodes->headNode;
    Block* block;
    while(node != NULL)
    {
        //write "nid: "  ************* buffSize-buffPointer is whatever char left in buffer
        buffPointer += snprintf(buffer + buffPointer, buffSize-buffPointer, "%d: ", node->nid);

        Block* block;
        if ( ( block = node->block) != NULL)
        {
            do
            {
                buffPointer += snprintf(buffer + buffPointer, buffSize-buffPointer, "%s, ", block->bid);
                buffer = resizeBuffer(buffer, buffPointer, &buffSize);
            } while( (block = block->prevBlock) != NULL );
        }
        node = node->nextNode;
        buffPointer += snprintf(buffer + buffPointer, buffSize-buffPointer, "\n");
    }

    printf("%s", buffer);
    free(buffer);
    return 0;
}

char* resizeBuffer(char* buffer, int buffPointer, int* buffSize)
{
    //check if buffPointer is approaching
    if(buffPointer < *buffSize * initSaturation) return buffer;

    *buffSize *= 2;

    buffer = realloc(buffer, *buffSize);

    return buffer;
}