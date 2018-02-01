#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c,s,area;
	scanf("%f,%f,%f,%f,%f\n",a,b,c,s,area);
	s=(a+b+c)/2;
	area=sqrt((s-a)*(s-b)*(s-c));
	printf("%f\n",area);
 } 
