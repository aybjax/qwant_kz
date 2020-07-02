#include <stdio.h>
#include <ctype.h>


int my_isupper(char soz);


/*int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_isupper(san));
    printf("if given belgi %c => %d\n", belgi, my_isupper(belgi));
    printf("if given basArip %c => %d\n", basArip, my_isupper(basArip));
    printf("if given arip %c => %d\n", arip, my_isupper(arip));

}*/

int my_isupper(char soz){
    if(isupper(soz))
        return 1;
    return 0;
}