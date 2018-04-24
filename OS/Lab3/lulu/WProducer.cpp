#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//随机数1-100
int get_random()
{
	int t;
	srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	t = rand() % 100 + 1;
	return t;
}
int main()
{
	SYSTEMTIME systime;
	//打开文件映射对象,成功返回文件映射对象句柄，否则0
	HANDLE hMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, "buffer");
	//将文件对象映射到进程地址空间，成功返回文件映射在内存中的起始地址，否则0
	LPVOID pfile = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
	//定义地址指针，指向内存首地址
	int* pData = reinterpret_cast<int*>(pfile);
	//打开信号量对象,成功返回信号量对象句柄，否则NULL
	HANDLE E_Handle = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Empty");
	HANDLE F_Handle = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Full");
	//打开互斥体对象，成功返回互斥体对象句柄，否则FALSE
	HANDLE Mutex_Handle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Mutex");
	//重复6次
	for (int i = 0; i<6; i++)
	{
		//随机等待一段时间
		Sleep(get_random());
		//等待信号量和互斥体
		WaitForSingleObject(E_Handle, INFINITE);
		WaitForSingleObject(Mutex_Handle, INFINITE);
		printf("生产者——");
		//添加数据时间
		GetLocalTime(&systime);
		printf("时间 %02d:%02d:%02d\t", systime.wHour, systime.wMinute, systime.wSecond);
		//添加数据
		int data = get_random();
		printf("放入数据:%d\t",data);	
		int put = *pData;
		*(pData + put * 4 + 8) = data;
		if (++put > 2)put = 0;
		*pData = put;
		printf("缓存状态:%d %d %d\n", *(pData + 8), *(pData + 12), *(pData + 16));
		//释放Full信号量,以唤醒消费者进程
		ReleaseSemaphore(F_Handle, 1, NULL);
		//释放互斥体
		ReleaseMutex(Mutex_Handle);
	}
	//关闭句柄
	CloseHandle(hMapping);
	CloseHandle(E_Handle);
	CloseHandle(Mutex_Handle);
	CloseHandle(F_Handle);
	return 0;
}

