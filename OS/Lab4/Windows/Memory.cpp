#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<Shlwapi.h>
#include<string.h>
#include<stdlib.h>
#include<TlHelp32.h>		//引用ToolHelp API，调用PROCESSENTRY32结构体
#include<iomanip>
/*
iomanip操纵运算子
setbase(int n)将数字转换为n进制
setw(n) 预设定宽度
*/

//连接动态链接库
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Kernel32.lib")

using namespace std;

void GetMemoryInfo()
{
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);

	//setw(20)用来设置宽度，对齐
	cout << setw(20) << "处理器掩码: " << si.dwActiveProcessorMask << endl
		<< setw(20) << "处理器个数: " << si.dwNumberOfProcessors << endl
		<< setw(20) << "处理器分页大小: " << si.dwPageSize << endl
		<< setw(20) << "处理器类型: " << si.dwProcessorType << endl
		<< setw(20) << "最大寻址单元: " << si.lpMaximumApplicationAddress << endl
		<< setw(20) << "最小寻址单元: " << si.lpMinimumApplicationAddress << endl
		<< setw(20) << "处理器等级: " << si.wProcessorLevel << endl
		<< setw(20) << "处理器版本: " << si.wProcessorRevision << endl;
}

void GetMemoryUsing()
{
	MEMORYSTATUSEX stat;
	stat.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&stat);
	long int DIV = 1024 * 1024;

	cout << setw(20) << "内存占用:" << stat.dwMemoryLoad << "%" << endl
		<< setw(20) << "总物理内存:" << stat.ullTotalPhys / DIV << "MB" << endl
		<< setw(20) << "可用物理内存:" << stat.ullAvailPhys / DIV << "MB" << endl
		<< setw(20) << "分页文件总量:" << stat.ullTotalPageFile / DIV << "MB" << endl
		<< setw(20) << "空闲分页文件量:" << stat.ullAvailPageFile / DIV << "MB" << endl
		<< setw(20) << "虚拟内存总量:" << stat.ullTotalVirtual / DIV << "MB" << endl
		<< setw(20) << "空闲虚拟内存总量:" << stat.ullAvailVirtual / DIV << "MB" << endl;
}

//显示当前块页面保护方式
void ShowProtection(DWORD dwTarget)
{
	printf(",");
	if (dwTarget == PAGE_READONLY)printf("PAGE_READONLY");
	if (dwTarget == PAGE_READWRITE)printf("PAGE_READWRITE");
	if (dwTarget == PAGE_WRITECOPY)printf("PAGE_WRITECOPY");
	if (dwTarget == PAGE_EXECUTE)printf("PAGE_EXECUTE");
	if (dwTarget == PAGE_EXECUTE_READ)printf("PAGE_EXECUTE_READ");
	if (dwTarget == PAGE_EXECUTE_READWRITE)printf("PAGE_EXECUTE_READWRITE");
	if (dwTarget == PAGE_EXECUTE_WRITECOPY)printf("PAGE_EXECUTE_WRITECOPY");
	if (dwTarget == PAGE_GUARD)printf("PAGE_GUARD");
	if (dwTarget == PAGE_NOACCESS)printf("PAGE_NOACCESS");
	if (dwTarget == PAGE_NOCACHE)printf("PAGE_NOCACHE");
}

//获得单个内存得使用情况
void LookVM(HANDLE hProcess)
{
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);				//获得系统信息

	LPCVOID start = (LPVOID)si.lpMinimumApplicationAddress;
	LPCVOID end = (LPCVOID)si.lpMaximumApplicationAddress;

	MEMORY_BASIC_INFORMATION mbi;	//进程虚拟内存空间得基本信息结构
	ZeroMemory(&mbi, sizeof(mbi));	//分配换成去，用于保存信息
									/*typedef struct MEMORY_BASIC_INFORMATION {
									PVOID BaseAddress;       // 区域基地址。
									PVOID AllocationBase;    // 分配基地址。
									DWORD AllocationProtect; // 区域被初次保留时赋予的保护属性。
									SIZE_T RegionSize;       // 区域大小（以字节为计量单位）。
									DWORD State;             // 状态（MEM_FREE、MEM_RESERVE或 MEM_COMMIT）。
									DWORD Protect;           // 保护属性。
									DWORD Type;              // 类型。
									} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;*/

	//循环遍历整个用用程序得地址空间
	while (start < end)
	{
		//获得下一个虚拟内存块得信息
		if (VirtualQueryEx(hProcess, start, &mbi, sizeof(mbi)) == sizeof(mbi))
		{
			//计算每个块得结尾及长度
			LPCVOID pEnd = (PBYTE)start + mbi.RegionSize;

			//显示块地址和长度
			char szSize[MAX_PATH];
			StrFormatByteSizeA(mbi.RegionSize, (PSTR)szSize, MAX_PATH);
			printf("块地址：%08x-%08x 共%s,", (DWORD)start, (DWORD)pEnd, szSize);
			
			//显示块的状态
			if (mbi.State == MEM_COMMIT)printf("COMMIT");
			if (mbi.State == MEM_FREE)printf("FREE");
			if (mbi.State == MEM_RESERVE)printf("RESERVE");

			//显示保护 
			if (mbi.Protect == 0 && mbi.State != MEM_FREE) {
				mbi.Protect = PAGE_READONLY;
			}
			ShowProtection(mbi.Protect);

			//显示类型 邻近页面物理存储器类型指的是与给定地址所在页面相同的存储器类型
			if (mbi.Type == MEM_IMAGE)printf(",Image");
			if (mbi.Type == MEM_MAPPED)printf(",Mapped");
			if (mbi.Type == MEM_PRIVATE)printf(",Private");

			printf("\n");
			//移动块指针以获得下一个块 
			start = pEnd;
		}
	}

}

void SearchProcessID()
{
	int id = 0;
	cout << "查询进程PID:" << endl;
	cin >> id;

	//打开进程对象
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, id);
	LookVM(hProcess);
}

void GetProcessInfo()
{
	PROCESSENTRY32 pro;//定义进程信息结构
	pro.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    //获取进程列表，最后一个参数是0,创建系统当前进程快照

	BOOL flag = Process32First(hProc, &pro);//从第一个进程开始
	//遍历进程快照
	while (flag)
	{
		printf("进程名称：%35ls\t", pro.szExeFile);//序号，进程名
		printf("PID : %d\t", pro.th32ProcessID);//PID
		printf("线程个数 : %d\n", pro.cntThreads);//此进程开启的线程数
		flag = Process32Next(hProc, &pro);
	}

	SearchProcessID();
	CloseHandle(hProc);
}

int main()
{
	char temp;
	cout << "内存管理" << endl;

	while (1)
	{
		cout << "请选择功能:" << endl;
		cout << "1 - 查看内存配置" << endl;
		cout << "2 - 查看内存使用" << endl;
		cout << "3 - 查看当前进程" << endl;
		cout << "0 - 退出" << endl;

		cin >> temp;
		switch (temp)
		{
		case'1':
			GetMemoryInfo();
			break;
		case'2':
			GetMemoryUsing();
			break;
		case'3':
			GetProcessInfo();
			break;
		case'0':
			cout << "ByeBye" << endl;
			return 0;
		default:
			cout << "非法输入" << endl;
			break;
		}
	}
	return 0;
}