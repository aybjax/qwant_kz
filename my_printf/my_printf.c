#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

char* my_utoa(unsigned int unsigned_integer_to_convert_to_string, char number_system);

char* my_itoa(int int_to_convert_to_string);

char* my_ptoa(size_t pointer_value_convert_to_string);

int my_printf(char* fmt, ...);

char* argToA(char* given_part_of_str, va_list* va_list_argument_pointer, char* string_input_for_va_arg);

int main(){
    int d = -25;
    int o = 25;
    int u = 63;
    int x = 21;
    char c = 'e';
    char* s = ":::this string:::";
    int* p = &d;
    
    char*b = "return va is %d\n";

    char* a = "my_printf can work on different data\n\tint = %d, octal = %o, unsigned int = %u\n\thex = %x, as well as characters = %c\n\tstrings = %s; and pointers = %p\n";

    //printing by format

    printf(b, my_printf(a, d, o, u, x, c, s, p));
    //printf(b, printf(a, d, o, u, x, c, s, p));
    

    printf("\n\n\n");
    
//
    ////does not skip uncessarily
    a = "%-sign not always formatted, iff %followed by something else\n";

    printf(b, my_printf(a, p, u));
    //printf(b, printf(a, p, u));

printf("\n\n\n");
//
    ////can handle null values
    a = "Null str - %s and pointer %p\n";
    char* sN=NULL;
    int* pN = NULL;
    my_printf(a, sN, pN);
    //printf(a, p, u);

    printf("\n\n\n");

    my_printf("%d!\n", 0);
    my_printf("%o!\n", 0);
    my_printf("%u!\n", 0);
    my_printf("%x!\n", 0);    
}


int my_printf(char* format, ...){
    //if string literal is passed, strtok will raise an erro
    //so, we need to copy its contents into buffer
    char fmt[strlen(format)+1];
    strcpy(fmt, format);

    //to avoid using write excessively => create buff of size 200 or more chars
    int buffSize = strlen(fmt)>200 ? strlen(fmt) + 50 : 200;

    //buff holds formatted string
    //char buff[buffSize];
    char* buff = calloc(buffSize, sizeof(char));
    printf("%p pointer\n", buff);

    //used in counting 
    int buffCounter = 0;

    //fined of strlen - later
    int len;


    //prepare vars for var args
    va_list args;
    va_start(args, format);

    //prepare placeholders for variable args
    int s_size=200;
            //char c, *s = (char*) calloc(s_size, sizeof(char)), *tok = (char*) calloc(s_size, sizeof(char)); -> changed
    char *s=NULL, *tok=NULL;


    //separate fmt into tokens by %
    char* sep = "%";
    //check if the first character is %
    //as first token may or may not be stating with %
    //if it is: it is similar to any other case (beg=1) else beg = 0
    int beg = fmt[0]=='%' ? 1 : 0;



    for(tok = strtok(fmt, sep); tok!=NULL; tok = strtok(NULL, sep)){
        if(beg)
            //always % before this token
            //string written instead of %c/%s...
            //s is string converted from formatting and arg
            s = argToA(tok++, &args, format);
        else
            //means -> very first token and no % before this => no need to format
            beg=1;

        
        if(s!=NULL){
            //s was assigned in if clause  => not in else clause
            len = strlen(s);
            for(int i = 0; i< len; i++)
                *buff++ = *s++;
                    ////set beginning of buff to beginning of s
                    //buff = s;
                    ////set pointer (cursor) to '\0' in buff (from s) to override it
                    //buff +=len;
            //modify counterBuff to get back to buff beginnign
                    //++ to know size of buff
            buffCounter += len;
            
            //free value calloc'ed in reverse fnx
            free(s);
        }

        //as above
        len = strlen(tok);
        for(int i = 0; i< len; i++)
            *buff++ = *tok++;
        //buff = tok;
        //buff +=len;
        buffCounter += len;
    }

    va_end(args);
    //write into stdout, buff-counter => move to beginning of pointer
                                //nbr of chars to printed
    write(1, buff-buffCounter, buffCounter);
    printf("%d buffCounter\n", buffCounter);

    printf("%p pointer before\n", buff);
    buff -= buffCounter;
    printf("%p pointer after\n", buff);
    free(buff);

    return buffCounter;
}


//given format and va_arg => returns string variant of var_arg (return value)
char* argToA(char* tok, va_list* args, char* fmt){
    //tok is incremented tok++ after input to this fnx

    //declare vars for capturing arg from va_arg
    int i;
    unsigned int u;
    size_t t;
    char c, *s;
    //placeholder used in default case
        //and to convert char to str
    char a[3];
    
    //print out parts between '%'
    //douxscp characters
    char fmtType;

    switch( fmtType= *tok){
        case 'u':
        case 'o':
        case 'x':
            u = va_arg(*args, unsigned int);
            //depending on type of fmtType
            s = my_utoa(u, fmtType);
            break;
        case 'c':
            c = (char) va_arg(*args, int);
            //return val is string =>
            *a = c;
            *(a+1) = '\0';
            s=a;
            break;
        case 's':
            s = va_arg(*args, char*);
            if(s==NULL)
                s="(null)";
            break;
        case 'd':
            i = va_arg(*args, int);
            //depending on whether u or not
                s = my_itoa(i);
            break;
        case 'p':
            t = va_arg(*args, size_t);
            //depending on whether u or not
                s = my_ptoa(t);
            break;
        default:
            //if % was not part of string formatting...
            //need to return % + 1char as tok++ before entering the fnx
            a[0] = '%';
            a[1] = *tok;
            a[2] = '\0';
            s = a;
    }
    return s;
}


//used inside my_itoa to reverse string
char* reverse(char* s){
    int len = strlen(s);
    char* result = (char*) calloc(len+1, sizeof(char));
    int i, rev;
    for(i = 0, rev=len-1; rev>=0; i++, rev--)
        result[i]=s[rev];
    result[i] = '\0';
    return result;
    }

//converts uint to corresponting string of int digits in dec/octal/hex
char* my_utoa(unsigned int d, char system){
    //divisor implies conversion to special system (dec, octal, hex)
    int div;
    switch(system){
        case 'u':
            div=10;
            break;
        case 'o':
            div=8;
            break;
        case 'x':
            div=16;
            break;
    }

    //size of str arr     // counters keeps array size in check
    int size = 10, counter = 0;

    //to divide each letter we need to put it
    char* s = (char*)calloc(size, sizeof(char));

    //mod of nbr/div
    int mod;

    //separate declaration as to add '\0'
    int index=0;

    //if d==0 => it will never enter the loop below
    if(d==0){
        return "0";
    }

    //  integer/integer=integer => last digits removed
    for(index = 0; d != 0;index++){
        mod = d % div;
        d = d/div;
                
        //int + 48 => ascii nbr
        if(mod<10)
            s[index] = mod+48;
        else
            //hex numbers have corresponding nbrs at +87
            s[index] = mod + 87;

        //if size is not enough
        if(++counter == size){
            size *= 2;
            s = (char*) realloc(s, sizeof(char)*size);
        }
    }

    //add '\0'
    s[index] = '\0';

    //result will hold the reverse
    //defined above
    char* result = reverse(s);

    free(s);
    return result;
}




//converts unsigned long to corresponting string of int digits
//copied from my_itoa
char* my_itoa(int d){
    //divisor implies conversion to special system (dec, octal, hex)
    int div;
    div=10;


    //sign of nbr    //0 is just a placeholder as cannot give ''
    char sign = d<0 ? '-' : 0;

    //because i to ascii conversion contains addition, we need to get rid of sign
    if(sign=='-')
        d*=-1;


    //size of str arr     // counters keeps array size in check
    int size = 10, counter = 0;

    //to divide each letter we need to put it
    char* s = (char*)calloc(size, sizeof(char));

    //mod of nbr/div
    int mod;

    //separate declaration as to add '\0'
    int index=0;

    //if d==0 => it will never enter the loop below
    if(d==0){
        return "0";
    }

    //  integer/integer=integer => last digits removed
    for(index = 0; d != 0;index++){
        mod = d % div;
        d = d/div;

        //int + 48 => ascii nbr
        s[index] = mod+48;

        //if size is not enough
        if(++counter == size){
            size *= 2;
            s = (char*) realloc(s, sizeof(char)*size);
        }
    }

    if(sign=='-')
        s[index++] = sign;
    s[index] = '\0';


    s[index] = '\0';

    //result will hold the reverse
    //defined above
    char* result = reverse(s);

    free(s);
    return result;
}

//copied from my_itoa
//size_t is used as it guarantees to hold the value
char* my_ptoa(size_t d){

    //check for null value
    if(d == (size_t) NULL){
        return "(nil)";
    }

    //divisor implies conversion to special system (dec, octal, hex)
    int div;
    div=16;

    //size of str arr     // counters keeps array size in check
    int size = 10, counter = 0;

    //to divide each letter we need to put it
    char* s = (char*)calloc(size, sizeof(char));

    //mod of nbr/div
    int mod;

    //separate declaration as to add '\0'
    int index=0;


    //  integer/integer=integer => last digits removed
    for(index = 0; d != 0;index++){
        mod = d % div;
        d = d/div;

        //int + 48 => ascii nbr
        if(mod<10)
            s[index] = mod+48;
        else
            s[index] = mod+87;

        //if size is not enough
        if(++counter == size){
            size *= 2;
            s = (char*) realloc(s, sizeof(char)*size);
        }
    }

    if(++counter > size-3){
            size += 5;
            s = (char*) realloc(s, sizeof(char)*size);
        }
    //add 0x before nbr
    s[index++]='x';
    s[index++]='0';

    s[index] = '\0';

    //result will hold the reverse
    //defined above
    char* result = reverse(s);

    free(s);
    return result;
}
