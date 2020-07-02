#include <stdio.h>
#include <ctype.h>


int my_isalpha(char soz);


/*int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_isalpha(san));
    printf("if given belgi %c => %d\n", belgi, my_isalpha(belgi));
    printf("if given basArip %c => %d\n", basArip, my_isalpha(basArip));
    printf("if given arip %c => %d\n", arip, my_isalpha(arip));

}*/

int my_isalpha(char soz){
    if(isalpha(soz))
        return 1;
    return 0;
}