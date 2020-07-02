#include <stdio.h>
#include <string.h>

int my_strcmp(char * string1, char* string2);

/*
int main(){
    printf("%i\n", my_strcmp("abc", "bd"));
    printf("%i\n", my_strcmp("bd", "abc"));
    printf("%i\n", my_strcmp("abc", "abc"));
}
*/

int my_strcmp(char* s1, char *s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len = len1>len2? len2 : len1;
    //int -> difference between 1st and 2nd ascii value
    int cmp;

    for(int i=0; i<=len; i++){
        cmp = s1[i] - s2[i];
        if(cmp<0){
            return -1;
        }else if(cmp>0){
            return 1;
        }
    }
    return 0;
}