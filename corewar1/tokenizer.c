# include "myHeader.h"

char* addSpaceAndLowerSpace(char* line);

InitLines* tokenizer(int file)
{
    char* line;
    char* lineSpaceAdded;

    //initLines
    InitLines* initLine = NULL;
    InitLines* tmpLine = NULL;
    InitLines* retLine = NULL;
    int counter=0;

    //initLexer
    InitLexer* initLexer = NULL;
    InitLexer* tmpLexer = NULL;

    String_array* tokens;

    while ((line = my_readline(file)) != NULL)
    {
        lineSpaceAdded = my_strip(addSpaceAndLowerSpace(line));

        if(lineSpaceAdded[0] == 0) goto skipTokenizing;

        tokens = my_split(lineSpaceAdded, SPACE);

        /*
        **
        */

        //sanity checks later

        //initiate beginning of lane
        initLine = malloc(sizeof(InitLines));
        if(counter++ == 0)
        {
            initLine->prev = NULL;
            retLine = initLine;
        }
        else
        {
            initLine->prev = tmpLine;
            tmpLine->next = initLine;
        }
        initLine->line = counter;
        initLine->next = NULL;

        /*
        **
        */
        //deal with tokens now
        for(int i=0; i<tokens->size; i++)
        {
            initLexer = malloc(sizeof(InitLexer));
            if(i == 0)
            {
                initLine->token = initLexer;
                initLexer->prev = NULL;
            }else
            {
                initLexer->prev = tmpLexer;
                tmpLexer->next = initLexer;
            }
            initLexer->next = NULL;
            // data assignment
            initLexerFill(initLexer, tokens->array[i]);
            //
            tmpLexer = initLexer;
        }


        tmpLine = initLine;

        /*
        **
        */

        free(tokens->array);
        free(tokens);
        skipTokenizing:
        free(line);
        free(lineSpaceAdded);
    }
    return retLine;
}

char* addSpaceAndLowerSpace(char* line)
{
    char* added;
    int size = strlen(line);
    int i, j;

    added = malloc(sizeof(char) * (size + 10));
    if(line[0] == 0)
    {
        added[0] = 0;
        return added;
    }
    for(i=0, j=0; i<size; i++)
    {
        if(line[i] == NEG_NUM || line[i] == COMMENT_CHAR || line[i] == LABEL_CHAR || line[i] == DIRECT_CHAR || line[i] == SEPARATOR_CHAR || line[i] == QUOTE_CHAR)
            if(i != 0) added[j++] = SPACE;
        
        if(line[i] >= 'A' && line[i] <= 'Z')
            added[j++] = line[i] + 'a' - 'A';
        else added[j++] = line[i];
        if(line[i] == NEG_NUM || line[i] == COMMENT_CHAR || line[i] == LABEL_CHAR || line[i] == DIRECT_CHAR || line[i] == SEPARATOR_CHAR || line[i] == QUOTE_CHAR)
            added[j++] = SPACE;
    }

    added[j] = 0;

    return added;
}