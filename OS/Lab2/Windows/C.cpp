#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<Windows.h>
#include<conio.h>
using namespace std;

int main()
{
	printf("Hello World!\n");
	while (1)
	{
		if (kbhit() != 0)
			break;
	}
	return 0;
}
