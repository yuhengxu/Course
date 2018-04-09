#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<string.h>

#define PROCESS_NUM 2
#define CUSTOMER_NUM 3

struct shareMemory
{
	int put;			//记录放数据得位置
	int take;			//记录取数据得位置
	int number[3];		//数据缓存区
};

//创建一个进程并赋予ID
HANDLE StartClone(const char* nCloneID)
{
	char szCmdLine_P[100] = "C:\\Users\\yuheng\\Desktop\\Lab3\\Windows\\Producer\\Debug\\";
	char szCmdLine_C[100] = "C:\\Users\\yuheng\\Desktop\\Lab3\\Windows\\Customer\\Debug\\";

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;

	BOOL bCreateOK;
	if (nCloneID == "Producer.exe")
	{
		strcat(szCmdLine_P, nCloneID);
		
		//创建子进程
		BOOL bCreateOK = CreateProcess(
			NULL,
			szCmdLine_P,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi);
	}
	else
	{
		strcat(szCmdLine_C, nCloneID);

		//创建子进程
		bCreateOK = CreateProcess(
			NULL,
			szCmdLine_C,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi);
	}

	if (!bCreateOK)
	{
		printf("Clone false\n");
		exit(-1);
	}

	return pi.hProcess;
}

//创建共享主存区
HANDLE MakeSharedFile()
{
	//创建文件映射对象
	HANDLE hMapping = CreateFileMapping(
		INVALID_HANDLE_VALUE,        //使用页式临时文件
		NULL,						 //缺省安全性
		PAGE_READWRITE,				 //可读写权
		0,							 //文件最大尺寸（高32位）
		sizeof(struct shareMemory),	 //文件最大尺寸（低32位）
		"buffer");					 //名
									 
	//在文件映射上创建视图
	if (hMapping != INVALID_HANDLE_VALUE)
	{
		LPVOID pData = MapViewOfFile(
			hMapping,					//文件映射对象的对象
			FILE_MAP_ALL_ACCESS,		//获得读写权
			0,							//在文件的开头处（高32位）开始
			0,							//在文件的开头处（低32位）
			0);							//映射整个文件
		if (pData != NULL)				//分配内存空间，并清0
		{
			ZeroMemory(pData, sizeof(struct shareMemory));
		}
		UnmapViewOfFile(pData);			//撤销文件映射对象
	}
	return (hMapping);                  //返回句柄
}


int main(int argc, char* argv[])
{
	printf("Mainprogram start:\n");

	//定义子进程句柄表
	HANDLE ChildProcessHandel[5];

	//创建数据文件
	HANDLE hMapping = MakeSharedFile();

	//创建互斥体对象，控制互斥访问缓冲池
	HANDLE Mutex = CreateMutex(
		NULL,			//缺省安全性
		FALSE,			//调用线程不能获取互斥体对象所属身份
		"Mutex");

	//创建信号量
	HANDLE Empty = CreateSemaphore(
		NULL,			//缺省安全性
		3,				//信号量初始为3
		3,				//信号量最大为3
		"Empty");

	HANDLE Full = CreateSemaphore(
		NULL,
		0,
		3,
		"Full");

	//创建生产者进程
	for (int i = 0; i < PROCESS_NUM; i++)
	{
		HANDLE ProducerHandle = StartClone("Producer.exe");
		ChildProcessHandel[i] = ProducerHandle;
	}
	for (int i = PROCESS_NUM; i < (PROCESS_NUM + CUSTOMER_NUM); i++)
	{
		HANDLE CustomerHandle = StartClone("Customer.exe");
		ChildProcessHandel[i] = CustomerHandle;
	}

	//等待子进程结束
	for (int i = 0; i < PROCESS_NUM + CUSTOMER_NUM; i++)
	{
		WaitForSingleObject(ChildProcessHandel[i], INFINITE);
		CloseHandle(ChildProcessHandel);
	}

	//关闭句柄
	CloseHandle(hMapping);
	CloseHandle(Empty);
	CloseHandle(Full);
	CloseHandle(Mutex);

	printf("Mainprocess Done!\n");
	system("pause");

	return 0;

}