#include "headers.h"

//returns prev or current node (if it is first)
Node* getNodeByNid(GlobalNode* nodes, int nid)
{
    //printf("getNodeByNid(%d)\n", nid);
    Node* node = nodes->headNode;
    Node* prev = node;

    //if * is given
    if(nid == INT_MAX) return node;

    if(node->nid == nid) return node;
    while ((node = node->nextNode) != NULL)
    {   
        printf("getNodebyNid\n");
        if(node->nid == nid) return node;
        prev = node;
    }

    return NULL;
}