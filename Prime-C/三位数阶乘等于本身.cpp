#include<stdio.h>
 int jiecheng(int n)
 {
 	int i,t=1;
 	for(i=1;i<=n;i++)
 		t*=i;
 	return t;
 }
int main()
{
	int a,b,c;
	for(a=1;a<10;a++)
		for(b=0;b<10;b++)
			for(c=0;c<10;c++)
			if(jiecheng(a)+jiecheng(b)+jiecheng(c)==a*100+b*10+c)
			printf("%d\n",a*100+b*10+c);
 } 

