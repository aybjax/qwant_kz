#include "headers.h"

int newBufferPointer(char* buffer, int buffPointer);
char* manageBufferSizeAndPointer(char* buffer, int* buffPointer, int* buffSize, int* ret);
char* resizeBuffer(char* buffer, int buffPointer, int* buffSize);
int listBlocks(char* buffer, int* buffPointer, int* buffSize, char* bid);

int listNodes(GlobalNode* nodes)
{
    int ret;
    char* retPointer;

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
        ret = snprintf(buffer + buffPointer, buffSize-buffPointer, "%d: ", node->nid);
        //return val of snprintf is what it would have written, NOT what ACTUALLY written
        buffer = manageBufferSizeAndPointer(buffer, &buffPointer, &buffSize, &ret);
        Block* block;
        if ( ( block = node->block) != NULL)
        {
            do
            {
                listBlocks(buffer, &buffPointer, &buffSize, block->bid);
            } while( (block = block->prevBlock) != NULL );
        }
        node = node->nextNode;
        strcpy(buffer+buffPointer++, "\n");
    }

    printf("%s\n", buffer);
    free(buffer);
    return 0;
}

char* resizeBuffer(char* buffer, int buffPointer, int* buffSize)
{
    //check if buffPointer is approaching
    if (*buffSize >= 100)
    {
        if(buffPointer < *buffSize * LARGE_FRACTION) return buffer;
    }else if(*buffSize > 20)
    {
         if(buffPointer < *buffSize * SMALL_FRACTION) return buffer;
    }

    *buffSize *= 2;

    buffer = realloc(buffer, *buffSize);

    return buffer;
}

char* manageBufferSizeAndPointer(char* buffer, int* buffPointer, int* buffSize, int* ret)
{
    *ret = *ret < *buffSize - *buffPointer ? *ret : *buffSize - *buffPointer;
    *buffPointer += *ret;
    buffer = resizeBuffer(buffer, *buffPointer, buffSize);
    return buffer;
}

int newBufferPointer(char* buffer, int buffPointer)
{
    for(; buffer[buffPointer] !=0; buffPointer++);
    return buffPointer;
}

int listBlocks(char* buffer, int* buffPointer, int* buffSize, char* bid)
{
    strcpy(buffer+*buffPointer, bid);
    *buffPointer = newBufferPointer(buffer, *buffPointer);

    strcpy(buffer+*buffPointer, ", ");
    *buffPointer = newBufferPointer(buffer, *buffPointer);

    buffer = resizeBuffer(buffer, *buffPointer, buffSize);
    
    return 0;
}