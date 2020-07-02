#include <stdio.h>
char* my_strip(char* str_leave_only_one_space);

/*
int main(){
    char a[] = "complex ";
    printf("%s", my_strip(a));
    printf("///////////////n");
}
*/

char* my_strip(char* str){
    int spaceBefore = 1;
    int indexDest=0;
    int indexSource=0;

    while(1){
        //sanity check

        if(spaceBefore && str[indexSource]=='\0'){
            //return
            str[indexDest-1] = '\0';
            goto rezultat;
        }
        //two consequetive spaces
        else if(str[indexSource]==32 && spaceBefore){ // || (*str==32 && *(str+1)=='\0')){
            indexSource++;
            continue;
        //space is first encountered
        }else if(str[indexSource]==32){
            spaceBefore=1;

        //current char is not char
        }else{
            spaceBefore=0;
        }

        str[indexDest] = str[indexSource];
        if(str[indexSource]=='\0'){
            goto rezultat;
        }

        indexSource++;
        indexDest++;
    }

    rezultat:
    return str;

}