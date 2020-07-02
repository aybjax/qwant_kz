#include <stdio.h>
#include <stdlib.h>

char* my_strcpy(char* destination_string, char* source_string);


//int main(){
//    char a[]="";
//    char b[] = "abc";
//    printf("%s\n", my_strcpy(a, b));
//    //my_strcpy("abc", "bgc");
//}


char* my_strcpy(char* s1, char* s2){

    int len;
    for(len=0; s2[len] != '\0'; ++len);
    //char *buff = (char*) malloc(++len * sizeof(char));
    //printf("%i\n", (int) sizeof(buff));

    for(int i=0; !(/**s1=='\0' ||*/ s2[i]=='\0'); i++, s1++/*, buff++*/){
        *s1 = s2[i];
        //*buff = s2[i];
    }
    //*(++buff) = '\0';
    *(++s1) = '\0';

    return /*buff-len;*/s1-len;
}