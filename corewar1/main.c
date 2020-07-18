#include "myHeader.h"
#include "corewar1.h"


int main(int argc, int* argv)
{
    InitLines* initLines;

    int fd = open("./file.txt", O_RDONLY);

    initLines = tokenizer(fd);

    /*
    **
    */

    printInitLexerLines(initLines);


    /*
    **
    */


    freeInitLines(initLines);

    close(fd);

    return 0;
}