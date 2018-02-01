#include <string.h> 
#include <stdio.h> 
int main(void) 
{ 
	char a[100],b[100],c[100];
	gets(a);
	gets(b);
	gets(c);
    char *buf1 = a, *buf2 = b, *buf3 = c; 
    int ptr; 
    ptr = strcmp(buf2, buf1); 
    if (ptr > 0) 
       printf("buffer 2 is greater than buffer 1\n"); 
    else 
       printf("buffer 2 is less than buffer 1\n"); 
    ptr = strcmp(buf2, buf3); 
    if (ptr > 0) 
       printf("buffer 2 is greater than buffer 3\n"); 
    else 
       printf("buffer 2 is less than buffer 3\n"); 
    return 0; 
} 
