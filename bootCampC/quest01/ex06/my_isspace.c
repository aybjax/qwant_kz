#include <stdio.h>
#include <ctype.h>


int my_isspace(char soz);


/*int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_isspace(san));
    printf("if given belgi %c => %d\n", belgi, my_isspace(belgi));
    printf("if given basArip %c => %d\n", basArip, my_isspace(basArip));
    printf("if given arip %c => %d\n", arip, my_isspace(arip));

}*/

int my_isspace(char soz){
    if(isspace(soz))
        return 1;
    return 0;
}