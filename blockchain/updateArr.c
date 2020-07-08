#include "headers.h"

int updateArr(GlobalNode* nodes)
{
    //heapify
    heapify(nodes);

    //then the node with longest and newest block is the main
    //get the the node
    
    reNewNodesAccordingToHeap(nodes);

    return 0;
}


//changes position in heap with last el in heap
int drownId(GlobalNode* nodes, int id)
{
    int endPos = nodes->nbrNodes-1;
    //printf("endPos is %d\n", endPos);

    int endId = nodes->heapNodes[endPos];
    
    printf("id = %d, endId = %d\n", id, endId);
    swapHeap(nodes, id, endId);

    return 0;
}

//dont kno y wrote it
////changes position in heap with 1st el in heap
int floatId(GlobalNode* nodes, int id)
{
    int begId = nodes->heapNodes[0];
    
    swapHeap(nodes, id, begId);

    return 0;
}

//changes position in heap by id
int swapHeap(GlobalNode* nodes, /*int pos1, int pos2*/ int id1, int id2)
{

    //int id1 = nodes->heapNodes[pos1];
    //int id2 = nodes->heapNodes[pos2];

    int idErr = nodes->idErr;
    
    //correction
    int pos1 = nodes->posMapNodesById[id1-idErr];
    int pos2 = nodes->posMapNodesById[id2-idErr];

    //do swapping
    nodes->posMapNodesById[id1 - idErr] = pos2;
    nodes->heapNodes[pos2] = id1;

    nodes->posMapNodesById[id2 - idErr] = pos1;
    nodes->heapNodes[pos1] = id2;

    return 0;
}

//if id1>id2 1, if reverse -1, if eq => 0
int cmpHeap(GlobalNode* nodes, int pos1, int pos2)
{
    //printf("cmpHEAP(%d, %d)\n", pos1, pos2);
    int id1, id2, block1, block2, time1, time2;
    id1 = nodes->heapNodes[pos1];
    id2 = nodes->heapNodes[pos2];
    //kerek emes
    if(id1 == INT_MIN && id2 == INT_MIN)
    {
        //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, INT_MIN);
        return INT_MIN;
    }
    if(id1 == INT_MIN)
    {
        //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, -1);
        return -1;;
    }
    if(id2 == INT_MIN)
    {
        //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, 1);
        return 1;;
    }

    block1 = nodes->bNbrById[id1];
    block2 = nodes->bNbrById[id2];

    //more blocks => bigger
    if(block1 > block2)
    {
        //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, 1);
        return 1;
    }
    else if(block1 < block2)
    {
        //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, -1);
        return -1;
    }
    else
    {
        //newer => bigger
        time1 = nodes->timeById[id1];
        time2 = nodes->timeById[id2];
        if(time1 > time2)
        {
            //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, 1);
            return 1;
        }
        else if(time1 < time2)
        {
            //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, -1);
            return -1;
        }
    }
    //printf("cmpHEAP(%d, %d)=%d\n", pos1, pos2, 0);
    return 0;
}

int swapWith(GlobalNode* nodes, int pos, int rel)
{
    int ret;
    int* heap = nodes->heapNodes;
    int size = nodes->nbrNodes;
    int exchangeePos, exchangeeID, id;
    if(rel == CHILD)
    {
        int child1pos, child2pos, child1id, child2id, childPos, childId;
        child1pos = pos*2+1 < size ? pos*2+1 : -1;
        child2pos = pos*2+2 < size ? pos*2+2 : -1;
        //child1id = child1pos == -1 ? -1 : heap[child1pos];
        //child2id = child2pos == -1 ? -1 : heap[child2pos];
        if (child1pos != -1 && child2pos != -1)
        {
            printf("childs: pos1: %d, pos2: %d\n", child1pos, child2pos);
            exchangeePos = cmpHeap(nodes, child1pos, child2pos) < 0 ? child2pos : child1pos;
        }else if (child1pos != -1)
        {
            exchangeePos = child1pos;
        }else if (child2pos != -1)
        {
            exchangeePos = child2pos;
        }else
        {
            return -1;
        }
    }else if(rel == PARENT)
    {
        exchangeePos = (pos-1)/2;
    }

    ret = cmpHeap(nodes, pos, exchangeePos);

    if(rel == CHILD)
        if(ret >= 0 || ret == INT_MIN) return -1;
    if(rel == PARENT)
        if(cmpHeap(nodes, pos, exchangeePos) == 0 ||
            cmpHeap(nodes, pos, exchangeePos) == -1) return -1;
    
    swapHeap(nodes, pos, exchangeePos);
    return exchangeePos;
}

//sink it down until heap invariant is present
int sink(GlobalNode* nodes, int pos)
{
    while( (pos=swapWith(nodes, pos, CHILD)) != -1 );
    return 0;
}

int swimup(GlobalNode* nodes, int pos)
{
    int ret;
    while( (ret=swapWith(nodes, pos, PARENT)) != -1 );
}

int reNewNodesAccordingToHeap(GlobalNode* nodes)
{
    if(nodes->nbrNodes != 0)
    {
        //get node id
        int id, nid;
        Node* node;
        id = nodes->heapNodes[0];
        nid = nodes->nidById[id - nodes->idErr];
        node = getNodeByNid(nodes, nid);

        //make the nodes head block to point the node block
        //depricated
        //nodes->headBlock = node->block;
        return 0;
    }else return 1;
}

int heapify(GlobalNode* nodes)
{
    register int i, size = nodes->nbrNodes;

    for(i = size/2; i>=0; i--)
        sink(nodes, i);
    
    return 0;
}