#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<string.h>

//共享主存区结构
struct sharemen
{
	int put;           //记录放数据位置
	int take;          //记录取数据位置
	int number[3];     //数据缓存去
};

//创建一个克隆的进程并赋予其ID值
HANDLE StartClone(char* nCloneID)
{
	char szCmdLine[50] = "E:\\lab\\";
	strcat(szCmdLine, nCloneID);
	STARTUPINFO si;            
	ZeroMemory(reinterpret_cast<void*>(&si), sizeof(si));  //清零
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	//创建子进程
	BOOL bCreateOK = CreateProcess(
		NULL,
		szCmdLine,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);
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
		sizeof(struct sharemen),	 //文件最大尺寸（低32位）
		"buffer");					 //名字
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
			ZeroMemory(pData, sizeof(struct sharemen));
		}
		UnmapViewOfFile(pData);			//撤销文件映射对象
	}
	return (hMapping);                  //返回句柄
}

int main(int argc, char* argv[])
{
	printf("Mainprogram Start:\n");

	//定义子进程句柄表
	HANDLE proHandle[5];

	//创建数据文件
	HANDLE hMapping = MakeSharedFile();
	//创建互斥体对象，控制互斥的访问缓冲池
	HANDLE Mutex = CreateMutex(
		NULL,				//缺省安全性
		FALSE,				//调用线程不能获得互斥体对象所属身份
		"Mutex");
	//创建信号量
	HANDLE Empty = CreateSemaphore(
		NULL,				//缺省安全性
		3,					//初始允许3个槽打开
		3,					//仅允许有5个槽
		"Empty");

	HANDLE Full = CreateSemaphore(
		NULL,				
		0,
		3,
		"Full");
	//创建生产者进程
	for (int i = 0; i<2; i++)
	{
		HANDLE P_Handle = StartClone("Producer.exe");
		proHandle[i] = P_Handle;

	}
	//创建消费者进程
	for (int i = 2; i<5; i++)
	{
		HANDLE C_Handle = StartClone("Customer.exe");
		proHandle[i] = C_Handle;

	}	
	//等待子进程完成
	for (int j = 0; j < 5; j++)
	{
		WaitForSingleObject(proHandle[j], INFINITE);
		CloseHandle(proHandle[j]);
	}
	//关闭句柄
	CloseHandle(hMapping);
	CloseHandle(Empty);
	CloseHandle(Full);
	CloseHandle(Mutex);
	printf("Mainprogram Done! \n");
	system("pause");
	return 0;
}
