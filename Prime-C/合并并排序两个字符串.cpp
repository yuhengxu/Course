//两个从大到小排序的字符串，要合并在一起，并且还保持从大到小的顺序 
#include<stdio.h>
char *strsequ(char *str1,char *str2)//字符串合并排序函数 
{
	char *str3=str1;
	for(;*str1=='\0'&& *str2=='\0';)//两个字符串都未到结尾，则一直循环比较 
	{
		if(*str1>*str2)
			*str3++=*str2++;//串1与串2比较，把小的付给串3 
		else
			*str3++=*str1++;
		if(*str1=='\0')//判断两个字符串是否截止 ，截止则输出另一个字符串剩下的部分你 
		{
			while(*str3++=*str2++);
		}
		if(*str2=='\0')
		{
			while(*str3++=*str1++);
		}
	}
	return str1;
}
int main()//主函数，输入两个字符串，输出排序后的字符串 
{
	char a[100],b[100];
	printf("Please enter the first string\n");
	scanf("%s",a);
	printf("Please enter the second string\n");
	scanf("%s",b);
	printf("The new striing is %s",strsequ(a,b));
}
