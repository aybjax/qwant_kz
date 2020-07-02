#include "headers.h"

int createNode(GlobalNode* nodes, int nid)
{
    int ret=0;
    //check if nid exists
    if ( nidExists(nodes, nid) )
    {
        NODE_EXIST;
        return 1;
    }

    //create a node with appropriate id/nid and zero init'zed other properties
    Node* node = createNewNode(nodes, nid);

    if (node == NULL)
    {
        NO_RESOURCE;
        return 1;
    }

    //houseKeeping jobs with nodes
    if( nodes->nbrNodes == 0 )
    {   //very first node => it is headNode
        nodes->headNode = node;
    }
    else
    {   //point the final nodes pointer to it
        nodes->tailNode->nextNode = node;
    }
    nodes->tailNode = node;
    

    //adjunct array managments
    {
        register int idErr = nodes->idErr;
        register int id = node->id;
        register int nbr = nodes->nbrNodes;
        nodes->timeById[id-idErr] = 0;
        nodes->bNbrById[id-idErr] = 0;
        nodes->nidById[id-idErr] = nid;
        //nbr - before incrementation
        nodes->heapNodes[nbr] = id;
        nodes->posMapNodesById[id-idErr] = nbr;
    }
    //other properties of node
    {
        nodes->nbrNodes++;
            //if you add new node => it will have empty blocks
        //=> synchronization is lost if there was some nodes before
        if(nodes->nbrNodes != 1 /* && nodes->headBlock != NULL*/)
        {
            nodes->syncd = NODES_NOT_SYNCD;
        }
    }
    //never happens
    if( (ret = hashTput(nodes, node)) == 1 )
    {
        printf("error");
        return 1;
    }

    //final step is to make sure enough space is left
    //if nodes are present populate arrays
    
    /** new node is  always empty **/
    /*ret = updateArr(nodes);*/
    
    if ( ret != 0 ) return ret;
    
    reallocArr(nodes);

    return 0;
}




Node* createNewNode(GlobalNode* nodes, int nid)
{
    Node* node = malloc(sizeof(Node));
    //printf("\n\nnode size is %d\n", (int)sizeof(struct node));
    //printf("nodes size is %d\n", (int)sizeof(struct governing_Or_Global_Struct_That_Contains_Every_Info_About_Nodes_And_Blocks));
    //printf("block size is %d\n\n\n", (int)sizeof(struct block));

    if (node == NULL)
    {
        NO_RESOURCE;
        return NULL;
    }
    
    //initialize node
    node->id = nodes->nextNodeId++;
    node->nid = nid;
    node->blockNbr = 0;
    node->timestamp = 0;
    node->nextNode = NULL;
    node->block = NULL;

    return node;
}

int hashTput(GlobalNode* nodes, Node* node)
{
    int tmpNid = hashTgetIndex(nodes, node, EMPTY);
    nodes->idByNid[tmpNid] = node->id;
    nodes->hashed++;
    return 0;
}

int hashTgetIndex(GlobalNode* nodes, Node* node, int exact)
{
    int tmpNid = my_hash(nodes, node->nid);
    int ret;

    while(true)
    {
        // //printNodes(nodes);
        // printf("tmpNid is %d\n", tmpNid);
        // printf("Nid = %d\n", node->nid);
        ret = nodes->idByNid[tmpNid];
        if( ret == INT_MIN && exact == EMPTY )
        {
            return tmpNid;
        }else if( ret != TOMBSTONE && exact == EXACT )
        {
            printf("nodes->nidById[%d]\n", ret);
            ret = nodes->nidById[ret-nodes->idErr];
            if( ret == node->nid ) return tmpNid;
        }
        tmpNid += linearProbing;
        tmpNid %= nodes->hashSize;
    }

    return 0;
}


int my_hash(GlobalNode* nodes, int nid)
{
    return nid%nodes->hashSize;
}