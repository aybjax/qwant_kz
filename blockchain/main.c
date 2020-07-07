#include "headers.h"
int interval_atoi(char* buff, int beg, int end);
int main()
{

    int ret, n;
    char c;

    GlobalNode* nodes = createNewSession();
    int* commands;


    if( nodes == NULL)
    {
        NO_RESOURCE;
        printf("errors\n");
        return 1;
    }

    do
    {
        
        commands = getCommand(nodes, &ret);
        printCommand(commands, ret);
        ret = parseCommand(nodes, commands, ret);
        free(commands);
        printNodes(nodes);
    } while (ret != QUIT);

    //printNodes(nodes);

    freeThemAll(nodes, ALL_MODE);
    return 0;
}