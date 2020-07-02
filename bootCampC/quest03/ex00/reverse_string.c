#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * reverse_string(char* text_to_reverse);


int main(){
    char a[] = "abcdefghig";
    reverse_string(a);
}


char * reverse_string(char* text){
    int nbr = strlen(text);
    char* buff = (char*) malloc(sizeof(char)*(nbr+1));
    *(buff+nbr) = '\0';
    buff=buff-nbr;

    /*
    strcpy(buff, text); 
    for(int i=0; *text != '\0'; i++, nbr--){
        //text[nbr] = buff[i];
        *(text+nbr) = *(buff+i);
    }
    */

    for(; nbr>=0; nbr--, buff++){
        *buff = *(text+nbr);
        printf("%s", text-nbr);
    }
    buff++;

    //printf("%s\n", buff);
    printf("%s\n", buff);
    return text-nbr;
}