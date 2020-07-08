#include "headers.h"

void printCommand(int* commands, int size)
{
    printf("\n");
    printf("input is:\n\t");
    for(int i=0; i<size; i++)
        {
            printf("%d ", commands[i]);
        }
    printf("\ninput size = %d\n", size);
}