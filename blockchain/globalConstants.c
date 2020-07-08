#include "headers.h"
/*
**
*/

//global constants
const char* LIST[2][COMMANDLENGTH] = {{ADD_STR,RM_STR,SYNC_STR,LSL_STR,QUIT_STR},{NODE_STR,BLOCK_STR,EMPTYCOMMAND,EMPTYCOMMAND,EMPTYCOMMAND}};
const fnx FNX[2][2] = { {createNode, createBlock}, {rmNode, rmBlock} };

const Block* BLOCK_TAIL;
const Node* NODE_HEAD;

/*
**
*/