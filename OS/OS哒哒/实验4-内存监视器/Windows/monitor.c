#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

#define WIDTH 26
#define KILO 1024ll
#define MEGA (KILO*KILO)
#define GIGA (MEGA*KILO)
#define TERA (GIGA*KILO)

void PrintHeader(char *field[], int width[], int num)
{
	for (int i = 0; i < num; i++)
	{
		char fmt[10];
		sprintf(fmt, "%%-%ds   ", width[i]);
		printf(fmt, field[i]);
	}
	printf("\n");
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < width[i]; j++) printf("-");
		printf("   ");
	}
	printf("\n");
}

int ListProcessModules(int pid)
{
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(
			TH32CS_SNAPMODULE, (DWORD)pid);
	if( hModuleSnap == INVALID_HANDLE_VALUE )
	{
		printf("Create module snapshot failed!\n");
		return 1;
	}

	char *field[] = {"Module Name", "Address", "Size(KB)", "Path"};
	int width[] = {20, 8, 8, 45};
	PrintHeader(field, width, 4);

	MODULEENTRY32 me32;
	me32.dwSize = sizeof( MODULEENTRY32 );
	BOOL bSucceed = Module32First(hModuleSnap, &me32);
	while (bSucceed)
	{
		printf("%-20s   ", me32.szModule);
		printf("%08x   ", me32.modBaseAddr);
		printf("%8d   ", me32.modBaseSize);
		char path[50];
		strncpy(path, me32.szExePath, 45);
		printf("%s\n", path);
		bSucceed = Module32Next(hModuleSnap, &me32);
	}
	CloseHandle(hModuleSnap);
	return 0;
}

void GetState(DWORD mbiState, char state[])
{
	switch (mbiState)
	{
		case MEM_COMMIT: strcpy(state, "Committed"); break;
		case MEM_FREE: strcpy(state, "Free"); break;
		case MEM_RESERVE: strcpy(state, "Reversed"); break;
		default: strcpy(state, "Unknown"); break;
	}
}

void GetType(DWORD mbiType, char type[])
{
	switch (mbiType)
	{
		case MEM_IMAGE: strcpy(type, "Image"); break;
		case MEM_PRIVATE: strcpy(type, "Private"); break;
		case MEM_MAPPED: strcpy(type, "Mapped"); break;
		default: strcpy(type, ""); break;
	}
}

void GetProtect(DWORD mbiProtect, char protect[])
{
	strcpy(protect, "----");
	WORD wProtect = (WORD)(mbiProtect & 0x00ff);
	switch (wProtect)
	{
		case PAGE_EXECUTE: strncpy(protect, "--X", 3); break;
		case PAGE_EXECUTE_READ: strncpy(protect, "R-X", 3); break;
		case PAGE_EXECUTE_READWRITE: strncpy(protect, "RWX", 3); break;
		case PAGE_EXECUTE_WRITECOPY: strncpy(protect, "RCX", 3); break;
		case PAGE_NOACCESS: strncpy(protect, "---", 3); break;
		case PAGE_READONLY: strncpy(protect, "R--", 3); break;
		case PAGE_READWRITE: strncpy(protect, "RW-", 3); break;
		case PAGE_WRITECOPY: strncpy(protect, "-C-", 3); break;
		default: strncpy(protect, "---", 3); break;
	}
	if (mbiProtect & PAGE_GUARD) protect[3] = 'G';
	if (mbiProtect & PAGE_NOCACHE) protect[3] = 'N';
	if (mbiProtect & PAGE_WRITECOMBINE) protect[3] = 'B';
}

void PrintVirtulMemory(int pid)
{
	HANDLE hProcess = OpenProcess(
			PROCESS_ALL_ACCESS | PROCESS_VM_READ,
			FALSE, (DWORD)pid);
	if (hProcess == NULL)
	{
		printf("Open process '%d' failed!\n", pid);
		exit(1);
	}

	char *field[] = {
		"No.", "Address", "Size/B", "Pages", 
		"State", "Protect", "Type"};
	int width[] = {4, 17, 10, 6, 9, 7, 7};
	PrintHeader(field, width, 7);

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));

	int count = 0;
	LPCVOID pBlock = si.lpMinimumApplicationAddress;
	while (pBlock < si.lpMaximumApplicationAddress)
	{
		VirtualQueryEx(hProcess, pBlock, &mbi, sizeof(mbi));

		printf("%4d   ", ++count);
		LPCVOID pEnd = pBlock + mbi.RegionSize;
		printf("%08x-%08x   ", pBlock, pEnd);
		printf("%10u   ", mbi.RegionSize);
		printf("%6u   ", mbi.RegionSize / si.dwPageSize);

		char state[10];
		GetState(mbi.State, state);
		printf("%-9s   ", state);

		char protect[10] = "";
		if (mbi.State == MEM_COMMIT)
			GetProtect(mbi.Protect, protect);
		printf("%-7s   ", protect);

		char type[10];
		GetType(mbi.Type, type);
		printf("%-7s   \n", type);
		
		pBlock = pEnd;
	}
}

void PrintMemoryInfo()
{
	printf("Memory Infomation\n");
	printf("----------------------------------------\n");

	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(ms);
	GlobalMemoryStatusEx(&ms);

	printf("%-*s: %d%%\n", WIDTH, "Physical memory in use", 
			ms.dwMemoryLoad);
	printf("\n");

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("%-*s: %d KB\n", WIDTH, "Page size", 
			si.dwPageSize / KILO);
	printf("%-*s: 0x%08x\n", WIDTH, "Lowest memory address", 
			si.lpMinimumApplicationAddress);
	printf("%-*s: 0x%08x\n", WIDTH, "Highest memory address", 
			si.lpMaximumApplicationAddress);
	printf("%-*s: %d KB\n", WIDTH, "Granularity", 
			si.dwAllocationGranularity / KILO);
	printf("\n");

	printf("%-*s: %.3lf MB\n", WIDTH,"Total physical memory", 
			(double)ms.ullTotalPhys / MEGA);
	printf("%-*s: %.3lf MB\n", WIDTH, "Available physical memory", 
			(double)ms.ullAvailPhys / MEGA);
	printf("\n");
	printf("%-*s: %.3lf MB\n", WIDTH, "Total page file", 
			(double)ms.ullTotalPageFile / MEGA);
	printf("%-*s: %.3lf MB\n", WIDTH, "Available page file", 
			(double)ms.ullAvailPageFile / MEGA);
	printf("\n");
	printf("%-*s: %.3lf TB\n", WIDTH, "Total virtual memory", 
			(double)ms.ullTotalVirtual / TERA);
	printf("%-*s: %.3lf TB\n", WIDTH, "Available virtual memory", 
			(double)ms.ullAvailVirtual / TERA);
	printf("\n");

	PERFORMANCE_INFORMATION pi;
	GetPerformanceInfo(&pi, sizeof(pi));
	printf("%-*s: %d Page\n", WIDTH, "Committed pages", pi.CommitTotal);
	printf("%-*s: %d Page\n", WIDTH, "System cache memory", pi.SystemCache);
	printf("%-*s: %d Page\n", WIDTH, "Total kernel pages", pi.KernelTotal);
	printf("%-*s: %d Page\n", WIDTH, "Paged kernel pages", pi.KernelPaged);
	printf("%-*s: %d Page\n", WIDTH, "Nonpaged kernel pages", pi.KernelNonpaged);
}

void PrintProcessorInfo()
{
	printf("Processor Information\n");
	printf("---------------------------------------\n");

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("%-*s: %d\n", WIDTH, "Processor architecture", 
			si.wProcessorArchitecture);
	printf("%-*s: %d\n", WIDTH, "Logical processors", 
			si.dwNumberOfProcessors);
	printf("%-*s: 0x%08x\n", WIDTH, "Processors mask", 
			si.dwActiveProcessorMask);
	printf("%-*s: %d\n", WIDTH, "Processor level", 
			si.wProcessorLevel);
	printf("%-*s: %d\n", WIDTH, "Processor revision", 
			si.wProcessorRevision);
	printf("\n");

	PERFORMANCE_INFORMATION pi;
	GetPerformanceInfo(&pi, sizeof(pi));
	printf("%-*s: %d\n", WIDTH, "Total processes", pi.ProcessCount);
	printf("%-*s: %d\n", WIDTH, "Total threads", pi.ThreadCount);
	printf("%-*s: %d\n", WIDTH, "Total handles", pi.HandleCount);
}

int PrintProcessList()
{
	char *field[] = {"Name", "PID", "PPID", "Threads", "Priority"};
	int width[] = {21, 5, 5, 7, 8};
	PrintHeader(field, width, 5);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot Failed!\n");
		return 1;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL bSucceed = Process32First(hProcessSnap, &pe32);
	while (bSucceed)
	{
		char name[30];
		strncpy(name, pe32.szExeFile, 21);
		printf("%-21s   ", name);
		printf("%5d   ", pe32.th32ProcessID);
		printf("%5d   ", pe32.th32ParentProcessID);
		printf("%7d   ", pe32.cntThreads);
		printf("%8d\n", pe32.pcPriClassBase);
		bSucceed = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return 0;
}

void PrintUsage()
{
	printf("monitor [/p] [/m] [/l] [/v <pid>] [/d <pid>]\n\n");
	printf("  %-10s", "/p");
	printf("Show processer infomation.\n");
	printf("  %-10s", "/m");
	printf("Show memory infomation.\n");
	printf("  %-10s", "/l");
	printf("List the running processes.\n");
	printf("  %-10s", "/s <pid>");
	printf("List the virtual memory of process <pid>.\n");
	printf("  %-10s", "/d <pid>");
	printf("List the modules of process <pid>.\n");
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("monitor: missing option\n\n");
		PrintUsage();
	}
	else if (strcmp(argv[1], "/?") == 0)
	{
		printf("Show system infomation.\n\n");
		PrintUsage();
	}
	else if (strcmp(argv[1], "/p") == 0)
	{
		PrintProcessorInfo();
	}
	else if (strcmp(argv[1], "/m") == 0)
	{
		PrintMemoryInfo();
	}
	else if (strcmp(argv[1], "/l") == 0)
	{
		PrintProcessList();
	}
	else if (strcmp(argv[1], "/v") == 0)
	{
		int pid = strtol(argv[2], NULL, 10);
		if (pid > 0) PrintVirtulMemory(pid);
		else printf("Invalid pid '%s'\n", argv[2]);
	}
	else if (strcmp(argv[1], "/d") == 0)
	{
		int pid = strtol(argv[2], NULL, 10);
		if (pid > 0) ListProcessModules(pid);
		else printf("Invalid pid '%s'\n", argv[2]);
	}
	else
	{
		printf("monitor: undefined option\n\n");
		PrintUsage();
	}
	return 0;
}
