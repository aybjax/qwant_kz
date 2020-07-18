#include "myHeader.h"

void freeInitLines(InitLines* initLines)
{
    InitLines* toDeleteLine = initLines;
    InitLines* nextLine;

    InitLexer* toDeleteLexer;
    InitLexer* nextLexer;

    while( toDeleteLine != NULL )
    {
        nextLine = toDeleteLine->next;

        toDeleteLexer = toDeleteLine->token;

        while( toDeleteLexer != NULL )
        {
            nextLexer = toDeleteLexer->next;
            free(toDeleteLexer->token);
            free(toDeleteLexer);
            toDeleteLexer = nextLexer;
        }
        free(toDeleteLine);
        toDeleteLine = nextLine;
    }
}