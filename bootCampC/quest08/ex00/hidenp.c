#include <stdio.h>
#include <stdlib.h>

int hidenp(char* str_to_search, char* has_letters_of_1st_str_in_exact_order);


int hidenp(char* str1, char* str2){
    //loop thru each string and jump to each other

    //char to comparare
    char tmp;
    //loop through str1
    int i=0;
    //loop though str2
    int j=0;


    for(; str1[i]!='\0'; i++){
        tmp = str1[i];
        goto Label2;
        Label1: continue;
    }

    //if every str1 character is found
    return 1;


    for(; str2[j]!='\0'; j++){
        Label2:
        if(str2[j]==tmp){
            goto Label1;
        }

    }

    //if any str1 character is NOT found
    return 0;

}