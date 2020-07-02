#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


void my_print_numbers();

void my_putchar(char c);
/*
int main(){
    my_print_numbers();
}*/

void my_print_numbers(){
    int i;
    for(i=48; i<=57; i++){
        my_putchar(i);
    }
    my_putchar('\n');
}

void my_putchar(char c) { write(1, &c, 1); }