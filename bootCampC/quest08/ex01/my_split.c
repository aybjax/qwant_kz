#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_string_array {
  int size;
  char** array;
} string_array;



string_array* my_split(char* text_to_separate, char* delimitor);



string_array* my_split(char* str, char* del){

    string_array* result = (string_array*) malloc(sizeof(string_array));


    if(strlen(del) == 0){
        result -> size = 0;
        result -> array = &str;
        return result;
    }


    //beginning of string: from beginning to delimiter is put into **array
    int beg = 0;

    //size of **arr
    int size=0;

    //initiate *arr with size 10
    //char** arr = (char**) calloc(0, sizeof(char*)); ----->>>> reallocation reverses arr order
    char** arr = (char**) calloc(10, sizeof(char*));

    for(int i=0;; i++){
        //no need to worry as separator is always a character
        if(str[i] == del[0]){
            //so that string end here, change delimiter to '\0'
            str[i] = '\0';

            //update arr size
            size += 1;


            //update arr size  ----->>>>> reallocation reverses arr order
            //arr = (char**) realloc(arr, size*sizeof(char*));


            //add new cut string pointer to arr
            arr[size-1] = &str[beg];

            //update beg as next char to str[i]
            beg = i+1;
        }else if(str[i]=='\0'){
            //this part captures string btw last-delimitor and end

            //update arr size
            size += 1;

            //update arr size
            //arr = (char**) realloc(arr, size*sizeof(char*));


            //add new cut string pointer to arr
            arr[size-1] = &str[beg];

            break;
        }
    }

    result -> size = size;
    result -> array = arr;

    return result;
}