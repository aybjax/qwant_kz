#include "headers.h"

void printNodes(GlobalNode* nodes)
{
    //system("clear");
    //nodes metadata
    printf("\n");
    ROW printf("\tidErr is => ");
    printf("%d\n", nodes->idErr);
    ROW printf("\tfirst node at => ");
    if(nodes->headNode == NULL) printf("%p\n", nodes->headNode);
    else printf("nid=%d\n", nodes->headNode->nid);
    ROW printf("\tlast node at => ");
    if(nodes->tailNode == NULL) printf("%p\n", nodes->tailNode);
    else printf("nid=%d\n", nodes->tailNode->nid);
    //ROW printf("\tnewest block at => "/*%p\n", nodes->headBlock*/);
    //if(nodes->headBlock == NULL) printf("%p\n", nodes->headBlock);
    //else printf("bid=%s\n", nodes->headBlock->bid);
    ROW printf("\tsynced? => %s\n", nodes->syncd == NODES_SYNCD ? "yes" : "no");
    ROW printf("\tnumber of nodes => %d\n", nodes->nbrNodes);
    ROW printf("\tid of next node => %d\n", nodes->nextNodeId);
    ROW printf("\tinitial adj array size => %d\n", nodes->initCapacity);
    ROW printf("\tinit hash table size => %d\n", nodes->initHash);
    ROW printf("\tcapacity of adjunct arrays => %d\n", nodes->cap);
    ROW printf("\tcapacity of hashTable => %d\n", nodes->hashSize);
    ROW printf("\tnumber of filled cells in HT => %d\n", nodes->hashed);
    ROW printf("\n");

printf("/****************************************************************************/\n");

    //print arrays
    //nid
    printf("\nnid by id\n\t");
    for(register int i=0; i<nodes->cap; i++)
    {
        if(nodes->nidById[i] != INT_MIN)
            printf("%2d ", nodes->nidById[i]);
        else 
            printf("%2c ", 'N');
    }
    printf("\n\t");
    for(register int i=0; i<nodes->cap; i++)
        printf("%2d ", i);
    printf("\n");

    //block nbr
    printf("\nblock nbr by id\n\t");
    for(register int i=0; i<nodes->cap; i++)
    {
        if(nodes->bNbrById[i] != INT_MIN)
            printf("%2d ", nodes->bNbrById[i]);
        else 
            printf("%2c ", 'N');
    }
    printf("\n\t");
    for(register int i=0; i<nodes->cap; i++)
        printf("%2d ", i);
    printf("\n");


    //time
    printf("\ntime of last block by id\n");
    for(register int i=0; i<nodes->cap; i++)
    {
        if(nodes->timeById[i] != INT_MIN)
            printf("%10d ", nodes->timeById[i]);
        else 
            printf("%10c ", 'N');
    }
    printf("\n");
    for(register int i=0; i<nodes->cap; i++)
        printf("%10d ", i);
    printf("\n");


    //posMap heap
    printf("\nposition of heap by id\n\t");
    for(register int i=0; i<nodes->cap; i++)
    {
        if(nodes->posMapNodesById[i] != INT_MIN)
            printf("%2d ", nodes->posMapNodesById[i]);
        else 
            printf("%2c ", 'N');
    }

    printf("\n\t");
    for(register int i=0; i<nodes->cap; i++)
        printf("%2d ", i);
    printf("\n");


    //heap
    printf("\nheap \n\t");
    for(register int i=0; i<nodes->cap; i++)
    {
        if(nodes->heapNodes[i] != INT_MIN)
            printf("%2d ", nodes->heapNodes[i]);
        else 
            printf("%2c ", 'N');
    }

    printf("\n\t");
    for(register int i=0; i<nodes->cap; i++)
        printf("%2d ", i);
    printf("\n");


    //hashTable
    printf("\nHashed: id by nid\n\t");
    for(register int i=0; i<nodes->hashSize; i++)
    {
        if(nodes->idByNid[i] == INT_MIN)
            printf("%2c ", 'N');
        else if(nodes->idByNid[i] == TOMBSTONE)
            printf("%2c ", 'X');
        else
            printf("%2d ", nodes->idByNid[i]);
    }

    printf("\n\t");
    for(register int i=0; i<nodes->hashSize; i++)
        printf("%2d ", i);
    printf("\n");


    printf("/****************************************************************************/\n");

    //nodes chain
    /*
    node nid => block <- block <-block
     /\
     ||
     \/
    node nide => block <-block
    */
    Node* node = nodes->headNode;
    Node* nextNode;
    while(node != NULL)
    {
        nextNode = node->nextNode;
        printf("\nnode #%d, nid: %d, hsBlock: %d => ", node->id, node->nid, node->blockNbr);
        Block* block;
        if ( ( block = node->block) == NULL)
        {
            printf("no block");
        }else
        {
            do
            {
                printf(" -> ");
                printf("block: %s", block->bid);
            } while( (block = block->prevBlock) != NULL );
        }

        printf("\n");
        if (nextNode == NULL) break;
        node = nextNode;
        printf(" /\\\n ||\n \\/");
    }
    printf("\n\n");
}