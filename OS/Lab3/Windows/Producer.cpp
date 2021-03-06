#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//随机数1-100
int my_random()
{
	srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	int t = rand() % 100 + 1;
	return t;
}

int main()
{
	SYSTEMTIME systime;

	//打开文件映射对象，成功返回文件映射对象句柄，否则返回0
	HANDLE hMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, "buffer");
	//将文件对象映射到进程地址空间，成功返回文件映射在内存中得起始地址，否则返回0
	LPVOID pfile = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
	//定义地址指针，指向内存首地址
	int* pData = reinterpret_cast<int*>(pfile);
	//打开信号量对象，成功返回信号量对象句柄表，否则返回FALSE
	HANDLE EMPTY_Handle = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Empty");
	HANDLE FULL_Handle = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Full");
	//打开互斥体对象，成功返回互斥体对象句柄，否则返回FALSE
	HANDLE MUTEX_Handle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Mutex");

	//重复6次
	for (int i = 0; i < 6; i++)
	{
		//随机等待一段时间
		Sleep(1000);
		//等待互斥体和信号量EMPTY进行P操作
		WaitForSingleObject(EMPTY_Handle, INFINITE);
		WaitForSingleObject(MUTEX_Handle, INFINITE);

		printf("Producer——");
		//添加数据时间
		GetLocalTime(&systime);
		printf("Using time: %02d:%02d:%02d  ", systime.wHour, systime.wMinute, systime.wSecond);
		//添加数据
		int data = my_random();
		printf("puts: %d  ", data);
		int put = *pData;
		*(pData + put * 4 + 8) = data;
		if (++put > 2)put = 0;
		*pData = put;
		printf("Buffer: %d %d %d\n", *(pData + 8), *(pData + 12), *(pData + 16));
		//对信号量FULL， Mutex进行V操作
		ReleaseSemaphore(FULL_Handle, 1, NULL);
		ReleaseMutex(MUTEX_Handle);

	}

	//关闭句柄
	CloseHandle(hMapping);
	CloseHandle(EMPTY_Handle);
	CloseHandle(MUTEX_Handle);
	CloseHandle(FULL_Handle);
	return 0;
}