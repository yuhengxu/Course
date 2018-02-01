#include<stdio.h>
#include<string.h>
int main()
{
    char a[100],b[100];
    int i,j,k;
    gets(a);
    gets(b);
    strcat(a,b);
    for(i=0;a[i]!='\0';i++)
    {
       for(j=i+1;a[j]!='\0';j++)
           if(a[i]>a[j])
             {
              k=a[i];
              a[i]=a[j];
              a[j]=k;
             }
    }
    puts(a);
    return 0;
}                                        
