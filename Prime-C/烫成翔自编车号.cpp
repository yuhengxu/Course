#include <stdio.h>  
  
int main ()  
{  
    char a[6];  
    int j;  
    char *op = a;  
    int  i= 0;  
      
    scanf ("%s", a);  
      
    for (j = 0; j < 4; j++)  
    {  
        if (*(op + j) >= 'A' && *(op + j) <= 'Z' && *(op + j) != 'I' && *(op + j) != 'O')  
        {  
            i ++;  
        }  
    }  
      
    if (i != 2)  
    {  
        printf ("no.\n");  
    }  
    if (i ==2)  
    {  
        if (*(op + j) >= '0' && *(op + j) <= '9')  
        {  
            printf ("ok.\n");  
        }  
        else  
        {  
            printf ("no.\n");  
        }  
    }  
}  

