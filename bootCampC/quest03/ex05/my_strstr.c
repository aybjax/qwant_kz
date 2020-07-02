#include <stdio.h>

char * my_strstr(char * text_to_be_searched, char * text_first_occurrence_is_serched_for);

/*
int main() {
    char a[] = "1234567aa";
    char b[] = "aaaaaa";
    printf("%s\n", my_strstr(a, b));
}
*/


char * my_strstr(char* lc, char* sc){
    if(sc[0]=='\0')
        goto emptyNeedle;
    int i;
    int j;
    //boolean: if sc and lc looped thru and no difference was found  => 1
    int similar=0;

    for(i=0; lc[i]!='\0'; i++){
        //printf("looping to %c\n", lc[i]);
        if (lc[i]==sc[0]){
            similar = 1;
            
            for(j=0; sc[j] != '\0'; j++){
                if(lc[j+i] == sc[j]){
                    //printf("\t%c and %c are similar\n", lc[j+i], sc[j]);
                    continue;
                }else {
                    similar=0;
                    //printf("\t%c and %c NOT similar\n", lc[j+i], sc[j]);
                    break;
                }
            }
        }
        if(similar)
            break;
    }
    if(similar!=0)
        return lc+i;
    else
        return NULL;// "NULL";
    emptyNeedle:
        return lc;
}