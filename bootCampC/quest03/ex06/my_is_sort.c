#include <stdio.h>
#include <stdbool.h>
/*
typedef int bool;
bool true = 1;
bool false = 0;
*/


typedef struct s_integer_array {
  int size;
  int* array;
} integer_array;

bool my_is_sort(integer_array* arr);


// int main(){
//     typedef integer_array arr;
//     int arr1[5] = {1, 1, 2 , 2, 1};
//     arr mine = {3, arr1};
//     printf("%d\n", my_is_sort(&mine));
// }

bool my_is_sort(integer_array* dict){
    //sign is used to take absolute value of difference btw consequitive arrays
    //it is used to use one algoriths for both ascending and desc arrrrays
    int sign;

    //printf("array is ");
    for(int i = 0; i<dict->size; i++)
    //    printf("%d ", dict->array[i]);
    //printf("\n");

    for(int i=0; i<dict->size-1; i++){
        if((dict->array[i]-dict->array[i+1]) > 0){
            sign = 1;
            break;
        }
        else if ((dict->array[i]-dict->array[i+1]) < 0){
            sign = -1;
            break;
        }
    }
    //printf("sign is %d\n", sign);

    for(int i=0; i<dict->size-1; i++){
        //expression under is positive or 0 as long as order in the beginning is held
        if( (dict->array[i]-dict->array[i+1]) * sign >= 0){
            //printf("array[%d] - array[%d] * sign = %d\n", dict->array[i], dict->array[i+1], (dict->array[i]-dict->array[i+1])*sign);
            continue;
        }
        else
            goto FALSE;
        
    }

    return true;

    FALSE:
    //printf("false\n");
    return false;

}