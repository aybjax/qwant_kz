//assumptions - search for exact text if want to know where used
/** new node is  always empty **/
/** use id-idErr only when dealiing with arrays, not fnx **/
/** add minimal and maximal saturation in reallocArr **/
/** cn use incomplete commands **/
/** even if all nodes have same block compositions,
 *       time of creation of outermost block matters **/

/*
**
*/
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>


/*
**
*/
//Error macros
#define COMMAND_NOT_FOUND fprintf(stderr, "COMMAND NOT FOUND\n")
#define NO_RESOURCE fprintf(stderr, "NO MORE RESOURCE AVAILABLE ON THE COMPUTER\n")
#define NODE_EXIST fprintf(stderr, "THIS NODE ALREADY EXISTS\n")
#define NODE_NO_EXIST fprintf(stderr, "NODE DOES NOT EXISTS\n")
#define BLOCK_EXIST fprintf(stderr, "THIS BLOCK ALREADY EXISTS\n")
#define BLOCK_NO_EXIST fprintf(stderr, "BLOCK DOES NOT EXISTS\n")

/*
**
*/


//Two partners can name same structures differently
//change the below macros to eliminate errors
#define bidLength 5
#define linearProbing 5

/*
**
*/
//macros for initBlockChain
#define initCap 2
#define initSaturation 0.4

#define NODES_SYNCD 's'
#define NODES_NOT_SYNCD '-'

/*
**
*/
//macros in createNode
#define TOMBSTONE (INT_MIN/2)
#define EMPTY 0
#define EXACT 1

/*
**
*/
//macros in printNodes
#define ROW printf("\t--------------------------------------\n");


/*
**
*/
//macros in getCommand.c
#define IN 0
#define BUFFSIZE 100

/*
**
*/
//macros in listNodes
//buffsize above

/*
**
*/

//macros in getCommand
#define SPACE 32

#define ADD_STR "add  "
#define RM_STR "rm   "
#define SYNC_STR "sync "
#define QUIT_STR "quit "
#define LSL_STR "ls -l"
#define BLOCK_STR "block"
#define NODE_STR "node "
#define EMPTYCOMMAND "     "

#define STRINGLEN (5+1)

//set according to LIST constant = LIST[2][COMMANDLENGTH]
#define COMMANDLENGTH 5

//two blocks below are indexes of LIST[0/1]
#define ADD 0
#define RM 1
#define SYNC 2
#define LS 3
#define QUIT 4

#define NODE 0
#define BLOCK 1


/*
**
*/
//macros in updateArr
#define CHILD 0
#define PARENT 1

/*
**
*/
//macros in initArr
#define NON_HASH 1
#define ALL (NON_HASH | HASH)

/*
**
*/
//macros in freeThemAll
#define NODE_FREE (NON_HASH<<2)
#define HASH (NON_HASH<<1)
//used is all, node, hash, nonhash
#define ALL_MODE (NODE_FREE | HASH | NON_HASH)

//define structures

typedef int (*fnx)();


typedef struct block
{
    char bid[bidLength];
    struct block* prevBlock;
} Block;


typedef struct node
{
    int id;
    int nid;
    int blockNbr;
    //seconds
        //redundant info(as it is in arrays)
    time_t timestamp;
    struct node* nextNode;
    Block* block;
} Node;

typedef struct governing_Or_Global_Struct_That_Contains_Every_Info_About_Nodes_And_Blocks
{
    Node* tailNode;
    Node* headNode;
    //dericated => as ech node has separate blocks
    //Block* headBlock;
    char syncd;
    int nbrNodes;
    int nextNodeId;

    //as id is incremented each time
        //if beginning id is deleted
        //it is always empty
    int idErr;
    //initCap saved
    int initCapacity;
    int initHash;

    //capacity of array/heap below
        //more than nbrOfnbrNodes
    int cap;
    /*********************************/
    //actual binary heap
        //size cap
        //value is id, index is ranking
        //parent>child
    int* heapNodes;
    //look up position of node in array/heap by id
        //size cap
        //index is id, value is ranming
    int* posMapNodesById;

    /*************************************/
    //how to find nodes by their id
        //size cap
    int* nidById;
    //find how many blocks are there by id
        //size cap
    int* bNbrById;
    //look up time of creation of last block by id
        //size cap
    int* timeById;

    //find ids by their nid
        //size big enough (<80% saturation)
        //power of 2 (to avoid infinite loops on linear probing) => GCD(primeNbr, 2**x) = 1
        //hashTable
    int* idByNid;
    //size of idByNid
    int hashSize;
    //how much table is occupied: data + tombstones
    int hashed;

} GlobalNode;

/*
**
*/
//functions
int initBlockChain( GlobalNode* nodes, int nbrOfNodes, Node* node, Block* block );

int createNode(GlobalNode* nodes, int nid);

int initNode(GlobalNode* nodes, Node* node);

int createBlock(GlobalNode* nodes, int nid, int bid);


int initBlock(Node* node, Block* block);

int mostSignBit(int size);

int updateArr(GlobalNode* nodes);

//inside updateArr
int swapHeap(GlobalNode* nodes, /*int pos1, int pos2*/int id1, int id2);
int drownId(GlobalNode* nodes, int id);
int floatHeap(GlobalNode* nodes, int id);
int cmpHeap(GlobalNode* nodes, int pos1, int pos2);
int swapWith(GlobalNode* nodes, int pos, int rel);
int sink(GlobalNode* nodes, int pos);
int swimup(GlobalNode* nodes, int pos);
int reNewNodesAccordingToHeap(GlobalNode* nodes);
int heapify(GlobalNode* nodes);

int initArr(GlobalNode* nodes, int allOrOnlyNonHash);

bool nidExists(GlobalNode* nodes, int nid);

GlobalNode* createNewSession();

void printNodes(GlobalNode* nodes);
void printCommand(int* commands, int size);

int* getCommand( GlobalNode* nodes, int* ret);

void freeThemAll( GlobalNode* nodes, int mode);
//inside freeThemAll
void freeBlock(Node* node);
void freeNode(GlobalNode* nodes);

/********************************/
int rmNode(GlobalNode* nodes, int nid);
//in  rmNode
int hashTrm(GlobalNode* nodes, Node* node);

int rmBlock(GlobalNode* nodes, int bid);

int syncNodes(GlobalNode* nodes);
//in syncNodes
bool isSyncd(GlobalNode* nodes);
int setSyncd(GlobalNode* nodes);
bool traverseAllBlocks(GlobalNode* nodes);

/*
**
*/
//inside createNode.c
Node* createNewNode(GlobalNode* nodes, int nid);
int hashTput(GlobalNode* nodes, Node* node);
int my_hash(GlobalNode* nodes, int nid);
int hashTgetIndex(GlobalNode* nodes, Node* node, int exact);

/*
**
*/

/*
**
*/
//inside getCommand.c
int* retriveCommandFromBuff(char* buff, int* ret);
int interval_atoi(char* buff, int beg, int end);
int getFirst2Commands(int* commands, int* index, char* buff, int beg, /*int end*/int* spaces, int spaceIndex);
int my_pow(int base, int power);
/*
**
*/

int parseCommand(GlobalNode* nodes, int* commands, int len);

Node* getNodeByNid(GlobalNode* nodes, int nid);

int syncNodes(GlobalNode* nodes);

//inside syncNodes
int reNewEachNodeBlock(GlobalNode* nodes);
int createBlockChain(Node* node, Block* headBlock);
int copyBlock(Block* block1, Block* block2);
int cpynodeMetaData(Node* blockNode, Node* node);
int deleteBlockChain(Block* block);
int reNewAdjArr(GlobalNode* nodes);

//inside rmBLock
int deleteBlock(GlobalNode* nodes, Node* node, int bid);

bool bidExists(Node* node, int bid);

//in bifExists
int mine_strcmp(char* s1, char* s2);

int reallocArr(GlobalNode* nodes);

int listNodes(GlobalNode* nodes);
//inside listNodes
char* resizeBuffer(char* buffer, int buffPointer, int* buffSize);
char* manageBufferSizeAndPointer(char* buffer, int* buffPointer, int* buffSize, int* ret);