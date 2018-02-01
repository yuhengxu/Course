#include<stdio.h>
char *strcat(char *str1,char *str2 )
{

	char *str3=str1;
	while(*str3!='\0')
		str3++;
	while(*str3++=*str2++);
	return str3;
} 
 int main()
 {
 	char a[30],b[30];
 	scanf("%s",a);
 	scanf("%s",b);
 	printf("%s",strcat(a,b));
 }
