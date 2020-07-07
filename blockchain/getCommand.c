#include "headers.h"

int* getCommand( GlobalNode* nodes, int* ret)
//commands initialized in retriveCommandFromBuff fnx
{
    //we use write bc it is system level as read
        //otherwise printf writes after read command
    char prompt_display[10];
    int nbr = snprintf(prompt_display, 10, "[%c%d]> ", nodes->syncd, nodes->nbrNodes);


    write(0, prompt_display, nbr);
    char buff[BUFFSIZE];
    {
    int red = read(IN, buff, BUFFSIZE);
    buff[red] = 0;
    }

    int* commands = retriveCommandFromBuff(buff, ret);

    //free(commands);
    return commands;
}

int* retriveCommandFromBuff(char* buff, int* ret)
{
    int words=1, buffLen=0, beg=0, end;
    //char* buffyonok;
    int index = 0;
    
    int* spaces = calloc(BUFFSIZE, sizeof(int));
    int spacesIndex=0;

    //get the size of tokens in buff
    for(buffLen=0; buff[buffLen] != 0; buffLen++)
    {
        if(buff[buffLen] == SPACE) 
        {
            //increment number of token in command
            words++;
            //because we need to know where spaces are
                //located in the command string
            spaces[spacesIndex++]=buffLen;
        }
    }
    //also put the end of buff to spacess
    //I dnot know why buffLen-1
    spaces[spacesIndex++] = buffLen-1;
    //printf("printing spaces...\n");
    for(int t=0; t<spacesIndex; t++)
    {
        //printf("%d", t);
    }
    //printf("\n");
    //for(int t=0; t<spacesIndex; t++)
    //{
    //    printf("%d", spaces[t]);
    //}
    //printf("\n");
    spacesIndex = 0;

    //if word are too small commands[1] might give overflow
    words = words>2 ? words : 2;
    
    //initialize commands
    int *commands = calloc(words, sizeof(int));

    //as calloc sets to 0 => need to distinguish error from 0
    commands[0] = -1;
    commands[1] = -1;

    //printf("array is %d\n", words);

    //find how many tokens are in the command
    //for(register int beg = 0, end; buff[beg] != 0; beg++)
    while(beg < buffLen)
    {
        end=*(spaces+spacesIndex++);
        //printf("end is %d\n", end);
        //printf("index is %d\n", index);
        if (index < 2)
        {
            getFirst2Commands(commands, &index, buff, beg, end);
            index++;
            //if command is sync/ quit / ls => only 1 argument
            if(commands[index-1]>=2) goto syncCommand;
        }
        else
        {
            int val = interval_atoi(buff, beg, end);
            //printf("val is %d\n", val);
            commands[index++] = val;
        }
        //printf("command - %d\n", commands[index-1]);

        //fixed
        beg = end+1;
    }
    syncCommand:
    free(spaces);
    //size of commands array
    *ret = index;
    return commands;
}

//converts chars from beg to end (inclusive, end=Length) to int
int interval_atoi(char* buff, int beg, int end)
{
    //printf("\nbuff is ::%s\nbeg is %d, end is %d\n", buff, beg, end);
    int ret=0, i=end-1, multiple=-1;
    for(; i>=beg; i--)
    {
        //printf("char is %c\n", buff[i]);
        if(buff[i]>='0' && buff[i]<='9')
        {
            if(++multiple!=0)
                ret += (buff[i]-'0') * my_pow(10, multiple);
            else
                ret += (buff[i]-'0');
        }
        else if(buff[i] == '*')
        {
            return INT_MAX;
        }
    }
    return ret;
}

int getFirst2Commands(int* commands, int* index, char* buff, int beg, int end)
{
    //in globalConstants.c
    extern const char* LIST[2][5];

    int j;
    //testing
    /*for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("LIST[%d][%d] = %s\n", i, j, LIST[i][j]);
        }
        printf("\n");
    }*/

    for(j=0; j<COMMANDLENGTH; j++)
    {
        register int k;
        //printf("\nLIST vs buff %c == %c\n", LIST[*index][j][0], buff[beg]);
        if( LIST[*index][j][0] == buff[beg])
        {
            for(k = 1; k<STRINGLEN && beg+k < end; k++)
            {
                //printf("LIST vs buff %c == %c", LIST[*index][j][k], buff[beg+k]);
                if( LIST[*index][j][k] != buff[beg+k]) return -1;
                //printf(" = > DONE\n");
            }
            //printf("from LIST is %s\n", LIST[*index][j]);
            
            /** cn use incomplete commands **/
            //if comment the if clause, cn write q instead of quit
            //if(LIST[*index][j][++k] != SPACE || LIST[*index][j][++k] != 0) return -1;
            
            break;
        }
    }
    //commands are interpreted as they appear in COMMANDS array
        //0 at index 0 is add, 1 at 0 - rm, 1 at 1 is block
    commands[*index] = j;
    return 0;
}

int my_pow(int base, int power)
{
    if(power == 1) return base;
    if(power == 0) return 1;
    return base * my_pow(base, power-1);
}