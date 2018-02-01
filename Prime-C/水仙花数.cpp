#include<stdio.h>
int cube(int a)
{
	return a*a*a;
 } 
 int main()
 {
 	int a,b,c;
 	for(a=1;a<=9;a++)
 		for(b=0;b<=9;b++)
 			for(c=0;c<=9;c++)
 			{
 				if(cube(a)+cube(b)+cube(c)==a*100+b*10+c)
 				printf("%d\n",a*100+b*10+c);
			 }
 }
