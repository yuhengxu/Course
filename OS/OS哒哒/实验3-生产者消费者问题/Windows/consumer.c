#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "header.h"

int main(int argc, char *argv[])
{
	int id = 0;
	if (argc > 1) id = strtol(argv[1], NULL, 10);
	srand(time(NULL));

	HANDLE hMapFile = OpenFileMapping(
			FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);

	HANDLE hEmptySemaphore = OpenSemaphore(
			SEMAPHORE_ALL_ACCESS, FALSE, SEM_EMPTY_NAME);
	HANDLE hFullSemaphore = OpenSemaphore(
			SEMAPHORE_ALL_ACCESS, FALSE, SEM_FULL_NAME);
	HANDLE hMutex = OpenMutex(
			MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);

	for (int i = 0; i < CONSUMER_CNT; i++)
	{
		WaitForSingleObject(hFullSemaphore, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);

		void *pBuf = MapViewOfFile(
				hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		int *pInt = pBuf;
		Data *pData = pBuf + 2 * sizeof(int);

		Sleep(rand() % (CONSUMER_IN_TIME + 1));
		int head = pInt[0];
		for (int j = 0; j < 21; j++) printf(" ");
		printf("Consumer%d <= %s   ", id, pData[head].s);
		strcpy(pData[head].s, "-----");
		head = (head + 1) % DATA_NUM;
		pInt[0] = head;

		for (int j = 0; j < DATA_NUM; j++)
			printf("%s ", pData[j].s);
		printf("\n");
		UnmapViewOfFile(pBuf);

		ReleaseSemaphore(hEmptySemaphore, 1, NULL);
		ReleaseMutex(hMutex);

		Sleep(rand() % (CONSUMER_OUT_TIME + 1));
	}

	CloseHandle(hEmptySemaphore);
	CloseHandle(hFullSemaphore);
	CloseHandle(hMutex);
	CloseHandle(hMapFile);
	return 0;
}
