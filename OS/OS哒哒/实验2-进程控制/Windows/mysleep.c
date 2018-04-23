#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	printf("Mysleep started.\n");
	int t = 0;
	if (argc > 1) t = strtol(argv[1], NULL, 10);
	if (t == 0)
	{
		srand(time(NULL));
		t = rand() % 1001;
	}
	printf("Sleep %d ms...\n", t);
	Sleep(t);
	printf("Mysleep finished.\n");
    return 0;
}
