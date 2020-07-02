#include <stdio.h>
#include <ctype.h>


int my_isdigit(char soz);


/*int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_isdigit(san));
    printf("if given belgi %c => %d\n", belgi, my_isdigit(belgi));
    printf("if given basArip %c => %d\n", basArip, my_isdigit(basArip));
    printf("if given arip %c => %d\n", arip, my_isdigit(arip));

}*/

int my_isdigit(char soz){
    if(isdigit(soz))
        return 1;
    return 0;
}