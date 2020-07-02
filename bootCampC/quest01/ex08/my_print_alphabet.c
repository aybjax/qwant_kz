#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


void my_print_alphabet();

void my_putchar(char c);
/*
int main(){
    my_print_alphabet();
}*/

void my_print_alphabet(){
    int i;
    for(i=97; i<=122; i++){
        my_putchar(i);
    }
    my_putchar('\n');
}

void my_putchar(char c) { write(1, &c, 1); }