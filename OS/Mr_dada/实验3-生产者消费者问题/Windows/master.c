#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "header.h"

HANDLE hMapFile;
HANDLE hEmptySemaphore;
HANDLE hFullSemaphore;
HANDLE hMutex;

void PrintHeader()
{
	char *head[] = {"Producer", "Consumer", "Buffer"};
	int width[] = {18, 18, 6 * DATA_NUM - 1};
	int num = 3;
	for (int i = 0; i < num; i++)
	{
		char fmt[10];
		sprintf(fmt, "%%-%ds", width[i]);
		printf(fmt, head[i]);
		printf("   ");
	}
	printf("\n");
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < width[i]; j++) printf("-");
		printf("   ");
	}
	printf("\n");
}

void CreateBuffer()
{
	DWORD dwMapSize = 2 * sizeof(int)
					  + DATA_NUM * sizeof(Data);
	hMapFile =  CreateFileMapping(
			INVALID_HANDLE_VALUE, NULL,
			PAGE_READWRITE, 0, dwMapSize, SHM_NAME);
	void *pBuf = MapViewOfFile(
			hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	int *pInt = pBuf;
	Data *pData = pBuf + 2 * sizeof(int);

	pInt[0] = pInt[1] = 0;
	for (int i = 0; i < DATA_NUM; i++)
		strcpy(pData[i].s, "-----");
	UnmapViewOfFile(pBuf);
}

void CreateSyncObjects()
{
	hEmptySemaphore = CreateSemaphore(
			NULL, DATA_NUM, DATA_NUM, SEM_EMPTY_NAME);
	hFullSemaphore = CreateSemaphore(
			NULL, 0, DATA_NUM, SEM_FULL_NAME);
	hMutex = CreateMutex(
			NULL, FALSE, MUTEX_NAME);
}

HANDLE StartProcess(char *name, int id)
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	char commandLine[10];
	sprintf(commandLine, "%s %d", name, id);

	BOOL bSucceed = CreateProcess(
			NULL, commandLine, NULL, NULL,
			FALSE, 0, NULL, NULL, &si, &pi);
	if (!bSucceed)
	{
		printf("Error: Master: Create process '%s' failed!\n", name);
		exit(1);
	}
	return pi.hProcess;
}

void CloseHandles()
{
	CloseHandle(hEmptySemaphore);
	CloseHandle(hFullSemaphore);
	CloseHandle(hMutex);
	CloseHandle(hMapFile);
}

int main(int argc, char *argv[])
{
	CreateBuffer();
	CreateSyncObjects();
	PrintHeader();

	HANDLE hProcesses[PRODUCER_NUM + CONSUMER_NUM];
	int iProcessTop = 0;
	for (int i = 1; i <= PRODUCER_NUM; i++)
	{
		HANDLE hProcess = StartProcess(PRODUCER_NAME, i);
		hProcesses[iProcessTop++] = hProcess;
	}
	for (int i = 1; i <= CONSUMER_NUM; i++)
	{
		HANDLE hProcess = StartProcess(CONSUMER_NAME, i);
		hProcesses[iProcessTop++] = hProcess;
	}

	for (int i = 0; i < iProcessTop; i++)
	{
		WaitForSingleObject(hProcesses[i], INFINITE);
		CloseHandle(hProcesses[i]);
	}
	CloseHandles();
	return 0;
}
