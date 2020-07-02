#include <stdio.h>

char* my_strrchr(char* text_to_be_searched, char searching_last_occurrence_of_char);

/*
int main(){
    char a[] = "abcabc";
    char b = 'd';
    printf("%s", my_strrchr(a, b));
}
*/


char* my_strrchr(char* text, char chr){
    int found=-1;

    int notNullTerminated = 1;
    for(int i;notNullTerminated;i++){
        if(text[i]==chr)
            found=i;
        if(text[i]=='\0')
            notNullTerminated=0;
    }
    if(found!=-1)
        return text+found;
    else
        return NULL;
}