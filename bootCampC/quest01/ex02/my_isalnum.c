#include <stdio.h>
//#include <regex.h>
//#include <ctype.h>


int my_isalnum(char soz);

/*
int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_isalnum(san));
    printf("if given belgi %c => %d\n", belgi, my_isalnum(belgi));
    printf("if given basArip %c => %d\n", basArip, my_isalnum(basArip));
    printf("if given arip %c => %d\n", arip, my_isalnum(arip));

}
*/
int my_isalnum(char soz){

    if((soz<=90 && soz >=65)||(soz>=97 && soz<=122)||(soz>=48 && soz<=57))
        return 1;
    return 0;

    /*
    if(isalnum(soz))
        return 1;
    return 0;
    */
    /*
    regex_t ptrn;
    int match = regcomp(&ptrn, "[[:alnum:]]", REG_ICASE);
    match = regexec(&ptrn, &soz, 0, NULL, 0);
    if(!match)
        return 1;
    return 0;*/
}