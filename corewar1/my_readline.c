#include "myHeader.h"

char* my_readline(int fd)
{
    char* str=NULL, *tmp=NULL;
    int ret, len, buffLen;
    //create buffer that hold info all read info
    //remembers across fnx calls
    static char buff[2048];
    while( true )
    {
        //if it is first declaration len = 0
        buffLen = strlen(buff);
        //read from file descriptor
        //read from where str ends
        ret = read(fd, &buff[buffLen], READLINE_READ_SIZE);
        //error
        if(ret == -1)
        {
            return NULL;
        }
        //if null and buff empty => return
        if(ret == 0 && strlen(buff) == 0)
        return NULL;
        //put \0 to where it was finisned reading
        if(ret != 0)
            buff[ret+buffLen] = TERM;
        //check if there is a \n
        tmp = strchr(buff, NL);
        //if NL exits
        if(tmp!=NULL)
        {
            //change \n to \0
            *tmp = TERM;
            //find len of line (including \0)
            len = tmp - buff + 1;
            //assign this val to str (including \0)
            str = calloc(len, sizeof(char));
            strncpy(str, buff, len);
            //set beginning of string to uncut part / term at \0 (TERM)
            len = strlen(tmp+1) + 1;
            //as memory blocks overlap
            memmove(buff, tmp+1, len);
            //exit(10);
            //return str
            return str;
        }
        else if(ret == 0)
        {
            //if no more \n and read not returning anything
            //return whole string
            len = strlen(buff) + 1;
            str = calloc(len, sizeof(char));
            strcpy(str, buff);
            return str;
        }
    }
}