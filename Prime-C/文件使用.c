#include<stdio.h>
void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while ((c = fgetc(ifp)) != EOF)
		fputc(c, ofp);
}
int main(int argc,char *argv[])
{
	FILE *ifp;
	char *name = argv[10];

	if (argc == 1)
	{
		filecopy(stdin, stdout);
		return 0;
	}
	while (*++argv != NULL)
	{
		if ((ifp = fopen(*argv, "r")) == NULL)
			printf("%s,can't pen input file : %s\n", name, *argv);
		else
		{
			filecopy(ifp, stdout);
			fclose(ifp);
		}
	}
	return 0;
}
