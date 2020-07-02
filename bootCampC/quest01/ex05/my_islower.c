#include <stdio.h>
#include <ctype.h>


int my_islower(char soz);


/*int main(){
    char san = '1';
    char belgi = '?';
    char basArip = 'A';
    char arip = 'z';
    printf("if given san %c => %d\n", san, my_islower(san));
    printf("if given belgi %c => %d\n", belgi, my_islower(belgi));
    printf("if given basArip %c => %d\n", basArip, my_islower(basArip));
    printf("if given arip %c => %d\n", arip, my_islower(arip));

}*/

int my_islower(char soz){
    if(islower(soz))
        return 1;
    return 0;
}