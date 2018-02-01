#include<stdio.h>
int main()
{
	int a,b,c,d,n=0;
	for(a=1;a<=6;a++)
	 for(b=1;b<=6;b++)
	  for(c=1;c<=6;c++)
	   for(d=1;d<=6;d++)
	   {
	   	if(a==b||a==c||a==d||b==c||b==d||c==d)
		   {
		   		continue;
		   }
		   if(a+b+c+d!=12)
		   {
		   		continue;
		   }
		   n++;
		   printf("{%d,%d,%d,%d}",a,b,c,d) ;
		   if(n%5==0)
		   {
		   	printf("\n");
		   }
		}
} 
