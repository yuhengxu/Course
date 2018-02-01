#include<stdio.h>
int main()
{
	int class1=0,class2=0,class3=0;
	char ch;
	do
	{
		ch=getchar();
		switch(ch)
		{
	
		case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'0':
		class1++;break;
		case'+':case'-':case'#':case'%':case'^':case'&':case'*':
		class2++;break;
		default:class3++;break;
		}
	} 
	while(ch!='\\');
	printf("\n class1=%d, class2=%d, class3=%d\n",class1,class2,class3);
	return 0;
}
