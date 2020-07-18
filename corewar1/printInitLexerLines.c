#include "myHeader.h"

void printTypes(int type);

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
                    printTypes(lexer->type);
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
    printf("\t%15d - %-40c - ", QUOTE_TYPE, QUOTE_CHAR);
    printTypes(QUOTE_TYPE);
    printf("\n");
    printf("\t%15d - %-40c - ", COMMENT_TYPE, COMMENT_CHAR);
    printTypes(COMMENT_TYPE);
    printf("\n");
    printf("\t%15d - %-40c - ", LABEL_TYPE, LABEL_CHAR);
    printTypes(LABEL_TYPE);
    printf("\n");
    printf("\t%15d - %-40c - ", DIRECT_TYPE, DIRECT_CHAR);
    printTypes(DIRECT_TYPE);
    printf("\n");
    printf("\t%15d - %-40c - ", SEPARATOR_TYPE, SEPARATOR_CHAR);
    printTypes(SEPARATOR_TYPE);
    printf("\n");
    printf("\t%15d - %-40s - ", NAME_CMD_TYPE, NAME_CMD_STRING);
    printTypes(NAME_CMD_TYPE);
    printf("\n");
    printf("\t%15d - %-40s - ", COMMENT_CMD_TYPE, COMMENT_CMD_STRING);
    printTypes(COMMENT_CMD_TYPE);
    printf("\n");
    printf("\t%15d - %-40s - ", LABEL_STRING_TYPE, LABEL_CHARS);
    printTypes(LABEL_STRING_TYPE);
    printf("\n");
    printf("\t%15d - %-40s - ", NUMBER_TYPE, NUMBER_CHARS);
    printTypes(NUMBER_TYPE);
    printf("\n");
    printf("\t%15d - %cNBR%-36s - ", REG_TYPE,REG_CHAR, " ");
    printTypes(REG_TYPE);
    printf("\n");
    printf("\t%15d - %-40s - ", UNKNOWN_TYPE, "UNKNOWN TYPE");
    printTypes(UNKNOWN_TYPE);
    printf("\n");
}


void printTypes(int type)
{
    if( type == QUOTE_TYPE ) printf("%-10s", "quote");
    if( type == COMMENT_TYPE ) printf("%-10s", "comm char");
    if( type == LABEL_TYPE ) printf("%-10s", "label char");
    if( type == DIRECT_TYPE ) printf("%-10s", "dir char");
    if( type == SEPARATOR_TYPE ) printf("%-10s", "separator");
    if( type == NAME_CMD_TYPE ) printf("%-10s", "prog name");
    if( type == COMMENT_CMD_TYPE ) printf("%-10s", "prog comm");
    if( type == LABEL_STRING_TYPE ) printf("%-10s", "any str");
    if( type == NUMBER_TYPE ) printf("%-10s", "nbr");
    if( type == REG_TYPE ) printf("%-10s", "registry");
    if( type == UNKNOWN_TYPE ) printf("%-10s", "unknown");
}