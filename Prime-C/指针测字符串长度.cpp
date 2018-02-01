#include<stdio.h>
	int  strlen(char *p)
	{
		int i=0;
		while(*p != '\0')
		{
			p++;
			i++;
		}
		return i;
	}
	int main()
	{
		char m[100] = { 0 };
		//scanf("%s", m);
		gets(m); 
		printf("%d",strlen(m));
	}
