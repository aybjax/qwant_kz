#include <stdio.h>

//fnx int -> 0 if negative && 1 if positive/0
int my_is_negative(int san);


/*int main(){
    const int NEGATIVE = -1;
    const int ZERO = 0;
    const int POSITIVE = 1;

    //sprintf("When input is %d output is %d\n", NEGATIVE, my_is_negative(NEGATIVE));
    //printf("When input is %d output is %d\n", ZERO, my_is_negative(ZERO));
    //printf("When input is %d output is %d\n", POSITIVE, my_is_negative(POSITIVE));
}*/

int my_is_negative(int nbr){
    if(nbr < 0)
        return 0;
    else
        return 1;
}