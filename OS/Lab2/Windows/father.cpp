#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<time.h>

int main(int argc, char *argv[])
{
	//????????????????????
	STARTUPINFO si;
	//??????????????????????????????��??????????????????
	PROCESS_INFORMATION pi;
	//????????
	SYSTEMTIME start, end;

	//ZeroMemory??0??????????????��???memset????
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	if (argc != 2)
	{
		printf("????????????��???��?????????");
		return 0;
	}

	GetSystemTime(&start);
	
	//?????????
	if (!CreateProcess(
		NULL,    //????��???��????????
		argv[1],                // ?????????????????????
		NULL,                   // ???????????
		NULL,                   // ???????????
		FALSE,                  // ????��????????
		CREATE_NEW_CONSOLE,     // ???????????????????????????????????????????????????
		NULL,                   // ????????????????�???????????????????????
		NULL,                   // ????????????��????????????????????��????????????
		&si,                    // ???STARTUPINFO???��??????
		&pi)                    // ???PROCESS_INFORMATION???��??????????????
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return 0;
	}

	//??????????????????
	WaitForSingleObject(pi.hProcess, INFINITE);

	GetSystemTime(&end);

	printf("Srart time is: %u:%u:%u:%u\n", start.wHour, start.wMinute, start.wSecond, start.wMilliseconds);
	printf("End time is: %u:%u:%u:%u\n", end.wHour, end.wMinute, end.wSecond, end.wMilliseconds);
	printf("Used time is: %u:%u:%u:%u\n", (end.wHour - start.wHour), (end.wMinute - start.wMinute), (end.wSecond - start.wSecond), (end.wMilliseconds - start.wMilliseconds));

	//????????
	CloseHandle(pi.hProcess);
}