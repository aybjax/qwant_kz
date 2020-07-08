#include "headers.h"

GlobalNode* createNewSession()
{
    GlobalNode* nodes = malloc(sizeof(GlobalNode));
    if (nodes==NULL)
    {
        NO_RESOURCE;
        return NULL;
    }
    if( !initBlockChain(nodes, 0, NULL, NULL) )
    {
        return nodes;
    }
    else return NULL;
}