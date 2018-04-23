#include <stdio.h>
#include <windows.h>

void Copy(const char srcPath[], const char dstPath[])
{
	WIN32_FIND_DATA ffd;
	FindFirstFile(srcPath, &ffd);
	if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		CopyFile(srcPath, dstPath, FALSE);
		return;
	}

	CreateDirectory(dstPath, NULL);
	char dir[MAX_PATH];
	sprintf(dir, "%s\\*", srcPath);
	HANDLE hFind = FindFirstFile(dir, &ffd);
	for (BOOL f = TRUE; f; f = FindNextFile(hFind, &ffd))
	{
		char *name = ffd.cFileName;
		if (strcmp(name, ".") == 0) continue;
		if (strcmp(name, "..") == 0) continue;
		char srcSubPath[MAX_PATH];
		sprintf(srcSubPath, "%s\\%s", srcPath, ffd.cFileName);
		char dstSubPath[MAX_PATH];
		sprintf(dstSubPath, "%s\\%s", dstPath, ffd.cFileName);
		Copy(srcSubPath, dstSubPath);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("mycp: msing file operand\n");
		printf("Usage: mycp <SRC> <DST>\n");
		return 1;
	}
	if (argc == 2)
	{
		printf("mycp: msing destination file ");
		printf("operand after '%s'\n", argv[1]);
		printf("Usage: mycp <SRC> <DST>\n");
		return 1;
	}
	Copy(argv[1], argv[2]);
	return 0;
}
