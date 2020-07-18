#include "myHeader.h"

int lexerFindType(char* str);
int isReg(char* str);
int isNum(char* str);
int isLabel(char* str);

int initLexerFill(InitLexer* lexer, char* str)
{
    int len = strlen(str) + 1;
    lexer->token = malloc(sizeof(char) * len);
    if(lexer->token == NULL) return -1;

    strcpy(lexer->token, str);

    lexer->type = lexerFindType(str);

    return 0;
}

int lexerFindType(char* str)
{
    if( *str == QUOTE_CHAR ) return QUOTE_TYPE;

    if( *str == COMMENT_CHAR ) return COMMENT_TYPE;

    if( *str ==  LABEL_CHAR ) return LABEL_TYPE;

    if( *str ==  DIRECT_CHAR ) return DIRECT_TYPE;

    if( *str ==  SEPARATOR_CHAR ) return SEPARATOR_TYPE;

    if( strcmp(NAME_CMD_STRING, str) == 0 ) return NAME_CMD_TYPE;

    if( strcmp(COMMENT_CMD_STRING, str) == 0 ) return COMMENT_CMD_TYPE;

    if( isReg(str) == 0 ) return REG_TYPE;

    if( isNum(str) == 0 ) return NUMBER_TYPE;

    if( isLabel(str) == 0 ) return LABEL_STRING_TYPE;

    return UNKNOWN_TYPE;
}

int isReg(char* str)
{
    //r0 to r16
    if(str[0] != REG_CHAR) return -1;
    if( isNum(str+1) != 0 ) return -1;
    int check = atoi(str+1);
    if(check > 16) return -1;
    return 0;
}

int isNum(char* str)
{
    if( str[0] != '-' && (str[0] > '9' || str[0] < '0') ) return -1;
    
    for(int i=1; str[i] != 0; i++)
    {
        if((str[i] > '9' || str[i] < '0') ) return -1;
    }

    return 0;
}

int isLabel(char* str)
{
    char tmp;
    for(int i=0; str[i] != 0; i++)
    {
        tmp = str[i];
        if( tmp != '-' && !(tmp<='9' && tmp>='0') && !(tmp<='z' && tmp>='a') )
            return -1;
    }
    return 0;
}