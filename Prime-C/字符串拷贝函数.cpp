#include <stdio.h> 
#include <string.h> 
int main(void) 
{ 
   char string[10]; 
   char *str1 = "abcdefghi"; 
   strcpy(string, str1); 
   printf("%sn", string); 
   return 0; 
} 
