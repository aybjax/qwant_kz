#include "headers.h"

int initNode(GlobalNode* nodes, Node* node)
{
    int ret;
    //create and append an empty node to nodes
    ret = createNode(nodes, node->nid);
    if (ret != 0)
    {
        printf("error");
        return ret;
    }
    //now when an empty node is created, it is in the tail of nodes
    nodes->tailNode->blockNbr = node->blockNbr;
    nodes->tailNode->timestamp = node->timestamp;
    
    //below is added here or on initBlock fnx
    //nodes->tailNode->block = node->block;

    return 0;
}