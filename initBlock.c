#include "headers.h"

int initBlock(Node* node, Block* block)
{

    //no need to create block
    //already created. it is just passed from serialized data
    //we need to connect the block to the node
    do
    {
        //something like this
        node->block = block;
    } while (++block==NULL);
    

    return 0;
}