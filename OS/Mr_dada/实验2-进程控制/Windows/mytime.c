#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
	{
		printf("The syntax of the command is incorrect.\n");
		printf("Usage: mytime <FILE> [OPTION]\n");
		return 1;
	}

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

	char arg[1024];
	strcpy(arg, argv[1]);
	for (int i = 2; i < argc; i++)
	{
		strcat(arg, " ");
		strcat(arg, argv[i]);
	}

    DWORD time = GetTickCount();
    BOOL bSucceed = CreateProcess(
            NULL, (LPTSTR)arg, NULL, NULL,
			FALSE, 0, NULL, NULL, &si, &pi);
    if (!bSucceed)
	{
		printf("Create process '%s' failed!\n", argv[1]);
		return 1;
	}
    WaitForSingleObject(pi.hProcess, INFINITE);
    time = GetTickCount() - time;

    printf("\nTime: %d ms\n", time);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
