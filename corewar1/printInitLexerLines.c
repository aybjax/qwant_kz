#include "myHeader.h"

int printInitLexerLines(InitLines* initLines)
{
    InitLines* lines = initLines;
    InitLexer* lexer;

    while( lines != NULL )
    {
        printf("\n");
        for(int i=0; i<2; i++)
        {
            lexer = lines->token;
            if(i == 0)
            {
                printf("%-2d --\\ ", lines->line);
                while(lexer != NULL)
                {
                    printf("%-10s", lexer->token);
                    if(lexer->next != NULL) printf(" %s ", "/--\\");
                    lexer = lexer->next;
                }
            }else
            {
                printf("\n");
                if(lines->next != NULL) printf("%-2s --/ ", " ");
                else printf("%-2s --/ ", " ");
                while(lexer != NULL)
                {
                    printf("%-10d", lexer->type);
                    if(lexer->next != NULL) printf(" %s ", "\\--/");
                    lexer = lexer->next;
                }
            }
        }

        {
            printf("\n\nLine #%d: ", lines->line);
            lexer = lines->token;
            while(lexer != NULL)
            {
                printf("%s ", lexer->token);

                lexer = lexer->next;
            }
            printf("\n");
        }

        if(lines->next != NULL)
        {
            printf("\n");
            printf("%-2s     ", "/\\");
            printf("\n");
            printf("%-2s     ", "||");
            printf("\n");
            printf("%-2s     ", "\\/");
            printf("\n");
        }
        lines = lines->next;
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");




    printf("example explained\n");

    {
        printf("Line number   --\\   value of token (string)  /--\\  value of next token     /--\\  ...\n");
        printf("              --/   type of token (integer)  \\--/  type (look below)       \\--/  ...\n");
        
        printf("/\\\n");
        printf("||\n");
        printf("\\/\n\n");

        printf("Line number   --\\   value of token (string)  /--\\  value of next token     /--\\  ...\n");
        printf("              --/   type of token (integer)  \\--/  type (look below)       \\--/  ...\n");
    }

    printf("\n");
    printf("\n");

    printf("types are as follows:\n");
    printf("\t%15d - %c\n", QUOTE_TYPE, QUOTE_CHAR);
    printf("\t%15d - %c\n", COMMENT_TYPE, COMMENT_CHAR);
    printf("\t%15d - %c\n", LABEL_TYPE, LABEL_CHAR);
    printf("\t%15d - %c\n", DIRECT_TYPE, DIRECT_CHAR);
    printf("\t%15d - %c\n", SEPARATOR_TYPE, SEPARATOR_CHAR);
    printf("\t%15d - %s\n", NAME_CMD_TYPE, NAME_CMD_STRING);
    printf("\t%15d - %s\n", COMMENT_CMD_TYPE, COMMENT_CMD_STRING);
    printf("\t%15d - %s\n", LABEL_STRING_TYPE, LABEL_CHARS);
    printf("\t%15d - %s\n", NUMBER_TYPE, NUMBER_CHARS);
    printf("\t%15d - %cNBR\n", REG_TYPE,REG_CHAR);
    printf("\t%15d - %s\n", UNKNOWN_TYPE, "UNKNOWN TYPE");
}