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
        printf("              --/   type of token (integer)  \\--/  type (look myHeader.h)  \\--/  ...\n");
        
        printf("/\\\n");
        printf("||\n");
        printf("\\/\n\n");

        printf("Line number   --\\   value of token (string)  /--\\  value of next token     /--\\  ...\n");
        printf("              --/   type of token (integer)  \\--/  type (look myHeader.h)  \\--/  ...\n");
    }

    printf("\n");
    printf("\n");
}