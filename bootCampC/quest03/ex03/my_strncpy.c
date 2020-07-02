#include <stdio.h>
#include <stdlib.h>

char* my_strncpy(char* destination_string, char* source_string, int nbr_to_copy);

/*
int main(){
    char a[10]="a";
    char b[] = "RaInB0w d4Sh! ";
    printf("%s\n", my_strcpy(a, b, 0));
}
*/

char* my_strncpy(char* s1, char* s2, int n){
    int i;
    if (n==0)
        goto result;
    for(i=0; i<n; i++, s1++){
        if (s2[i] == '\0')
            goto result;
        *s1 = s2[i];
    }
    ++s1;
    result:
    *s1 = '\0';
    return s1-++i;
}