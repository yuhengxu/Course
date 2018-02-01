#include<stdio.h>
#include<string.h>
int main()
{
	char words[5][15]={{'\0'},{'\0'},{'\0'},{'\0'},{'\0'}} ,temp[15]={0};
	int i,j;
	scanf("%s",words[0]);
	for(i=1;i<5;i++)
	{
		scanf("%s",temp);
		j=i-1;
		while(strcmp(temp,words[j])<0)
		{
			strcpy(words[j+1],words[j]);
			j--;
		}
			strcpy(words[j+1],temp);
	} 
	for(i=4;i>=0;i--)
	{
		printf("%s\n",words[i]);
	}
	return 0;
} 
