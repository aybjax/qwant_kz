#include "headers.h"

int rmNode(GlobalNode* nodes, int nid)
{
    Node* node = nodes->headNode;
    Node* prev = NULL;

    //nodes->nbrNodes not informative;
        //because highest id does not correspond to nbr of nodes
    register int nbr = nodes->nbrNodes;
    
    //this was added before introduction of while loop
    //register int iterate = nodes->nextNodeId;
    
    register int/* id, cap,*/i = 0, nodeId = nid;

    //for(/*i=0*/i = nodes->idErr; i< iterate; i++)
    while(node != NULL)
    {
        //delete all if * is given
        if(nodeId == INT_MAX) break;

        if(node->nid == nodeId)
        {
            //1st: adjunct array managments
            {
                //printf("\n\n*********-I was here***********\n\n");
                
                int register pos;
                register int id = node->id;
                register int idErr = nodes->idErr;
                //printf("id is %d\n", id);
                //printf("i is %i\n", i);

                //hashTable
                hashTrm(nodes, node);

                //or tombstone
                nodes->timeById[id-idErr] = INT_MIN;
                nodes->bNbrById[id-idErr] = INT_MIN;
                nodes->nidById[id-idErr] = INT_MIN;
            
                //in order to delete from heap
                    //we swap it with the last element
                    //then delete the last el
                    //before decrementing nodes->nbr
                
                ////added later
                ////get last el id
                //int lastId = nodes->heapNodes[nodes->nbrNodes-1];

                drownId(nodes, id);
                pos = nodes->posMapNodesById[id-idErr];
                //printf("pos is %d\n", pos);
                nodes->posMapNodesById[id-idErr]  =INT_MIN;
                nodes->heapNodes[pos] = INT_MIN;


                ////last el pos
                //pos = nodes->posMapNodesById[lastId];
                //sink(nodes, pos);
            }
            
            //nodes head and tail pointers
                //no need if deleting all nodes
            if(i==0)
            {
                if(nbr == 1)
                {   //if was the only node
                    nodes->tailNode = NULL;
                    nodes->headNode = NULL;
                }else
                    nodes->headNode = node->nextNode;
            }else if(i == nbr-1)
            {   //if last node
                nodes->tailNode = prev;
                prev->nextNode = NULL;
            }else
            {   //if not last node
                prev->nextNode = node->nextNode;
            }

            ////?????????????????????????????
            //if(strcmp(node->block->bid, nodes->headBlock->bid) == 0)
            //    nodes->headBlock = NULL;

            freeBlock(node);
            free(node);
            
            nodes->nbrNodes--;

            reallocArr(nodes);

            return 0;
        }
        
        //if NOT deleting all keep searching
        prev = node;
        node = node->nextNode;
        i++;
    }

    if(nid == INT_MAX)
    {//manage nodes metadata that we skipped above
        freeNode(nodes);
        initArr(nodes, ALL);
        nodes->tailNode = NULL;
        nodes->headNode = NULL;
        setSyncd(nodes);
        nodes->nbrNodes = 0;
        nodes->nextNodeId = 0;

        int reallocArr(GlobalNode* nodes);
        return 0;
    }

    return 1;
}

//modified hashTput
int hashTrm(GlobalNode* nodes, Node* node)
{
    int tmpNid = hashTgetIndex(nodes, node, EXACT);
    // printf("tmpNid = %d\n", tmpNid);
    nodes->idByNid[tmpNid] = TOMBSTONE;
    return 0;
}