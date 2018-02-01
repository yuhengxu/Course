#include<stdio.h>      
#include<string.h>      
int main()      
{      
    char a[100],b[100];      
    int j,i,c=1;      
    gets(a);      
    b[0]=a[0];      
   for(i=1;a[i]!='\0';i++)      
    {      
        for(j=0;j<c;j++)      
        {      
            if(b[j]==a[i])      
                break;      
       }      
        if(j==c)      
        {      
            b[j]=a[i];      
            c++;      
        }      
    }      
 b[c] = '\0' ;      
 puts(b);      
    return 0;      
}  

