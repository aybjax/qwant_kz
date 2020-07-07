#include "headers.h"

int parseCommand(GlobalNode* nodes, int* commands, int len)
{
    //extern const fnx FNX;
    //fnx* fnx;
    int ret = INT_MAX;
    int firstCommand = commands[0];
    int secondCommand = commands[1];

    if(len == 1)
    {
        if ( firstCommand == SYNC)
        {
            ret = syncNodes(nodes);
            printf("syncNode executed\n");
        }else if (firstCommand == LS)
        {
            //your code here
            firstCommand=LS;
        }else if (firstCommand == QUIT)
        {
            return QUIT;
        }
    }else if(firstCommand==ADD)
    {
        //fnx = FNX[0][0];
        //add node nid
        if(secondCommand == NODE)
        {
            if(len < 3) return 1;
            for(int i=2; i<len; i++)
            {
                ret = createNode(nodes, commands[i]);
                printf("creatNode(%d) executed\n", commands[i]);
            }
        }
        else if(secondCommand == BLOCK)
        {
            //add block bid nid*
            if(len < 4) return 1;
            for(int i=3; i<len; i++)
            {
                ret = createBlock(nodes, commands[i], commands[2]);
                printf("creatBlock(%d, %d) executed\n", commands[2], commands[i]);
            }
            //inside createBlock, setSyncd runs only if * is given as arguments
                //therefore need to make sure if instead of *, user provides
                //all nodes manually
            if(len > 4) setSyncd(nodes);
        }
    }else if(firstCommand==RM)
    {   //rm node nid*
        if(len < 3) return 1;
        for(int i=2; i<len; i++)
        {
            if(secondCommand==NODE)
            {
                ret = rmNode(nodes, commands[i]);
                printf("rmNode(%d) executed\n", commands[i]);
            }
            else if(secondCommand==BLOCK)
            {
                //rm block bid
                ret = rmBlock(nodes, commands[i]);
                printf("rmBlock(%d) executed\n", commands[i]);
            }
        }
    }else
    {
        COMMAND_NOT_FOUND;
    }
    
    if(ret==INT_MAX)
    {
        printf("nothing is executed\n");
    }
    

    return 0;
}