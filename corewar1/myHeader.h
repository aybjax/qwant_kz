# include "corewar1.h"
/*
** my_readline.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>
#include <stdbool.h>


#define READLINE_READ_SIZE 512
#define NL '\n'
#define TERM '\0'

/*
** my_split.c
*/

#define SPACE 32

typedef struct s_String_array {
  int size;
  char** array;
} String_array;


/*
** macros for lexer
**  cont of MEM_SIZE
*/

//  LineLexer types
    #define QUOTE_TYPE 0
    #define QUOTE_CHAR '"'

    #define COMMENT_TYPE 1 // #

    #define LABEL_TYPE 2 // :

    #define DIRECT_TYPE 3 // %

    #define SEPARATOR_TYPE 4 // ,

    #define NAME_CMD_TYPE 5 //.name

    #define COMMENT_CMD_TYPE 6 //.comment

    #define LABEL_STRING_TYPE 7 //all a-z | _ | 0-9 : comments, names, instructions

    #define NUMBER_TYPE 8 // 0-9
    #define NUMBER_CHARS "0123456789" //NUMBER_CHARS < LABEL_CHARS //not used
    #define NEG_NUM '-'

    #define REG_TYPE 9 // ^r & 0-9
    #define REG_CHAR 'r' //num of reg <=16

    #define UNKNOWN_TYPE -1
//

/*
**
*/

#define BYTE unsigned char


/*
** Lexer macros
**  continuation of T_REG/T_DIR
*/ 
# define T_INSTR 1 << 4
# define T_NAME 1 << 5
# define T_COMM 1 << 6
# define T_OTHER 1 << 7


//used for inital parsing of text into tokens
typedef struct line_lexer_s
{
    char* token;
    int type;  //above multiple types
    struct line_lexer_s* next;
    struct line_lexer_s* prev;
}
InitLexer;

//linkd list of LineLexers
    //represent each line
typedef struct start_s
{
    struct start_s* next;
    struct start_s* prev;
    InitLexer* token;
    int line;
}
InitLines;

//lexer from init vals
typedef struct lexer_s
{
    char* token;
    int type;
    BYTE* byteCode;
    int byteLen;
    int lineOrder;
    int tokenOrder;
    struct lexer_s* next;
    struct lexer_s* prev;
} Lexer;

typedef struct line_s
{
    int lineNum;
    Lexer* headLexer;
    struct line_s* next;
    struct line_s* prev;
    int bytesUpTo;
    int LineByte;
    BYTE argType; 
} Line;


/*
** fnxs
*/

char* my_readline(int fd);

String_array* my_split(char* text_to_separate, char delimitor1);

char* my_strip(char* str_leave_only_one_space);

InitLines* tokenizer(int file);

int iniLexerFill(InitLexer* lexer, char* str);

void freeInitLines(InitLines* initLines);

int printInitLexerLines(InitLines* initLines);