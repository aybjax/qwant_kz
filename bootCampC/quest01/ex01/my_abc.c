#include <stdio.h>

int my_abs(int san);

/*
int main(){
    const int NEGATIVE = -1;
    const int ZERO = 0;
    const int POSITIVE = 1;

    printf("When input is %d output is %d\n", NEGATIVE, my_abs(NEGATIVE));
    printf("When input is %d output is %d\n", ZERO, my_abs(ZERO));
    printf("When input is %d output is %d\n", POSITIVE, my_abs(POSITIVE));
}


*/


int my_abs(int nbr){
    if(nbr<0)
        nbr *= (-1);
    return nbr;
}