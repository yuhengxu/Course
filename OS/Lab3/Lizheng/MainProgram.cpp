#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#define Producer_Num 2
#define Customer_Num 3
HANDLE StartClone(char* Process_ID)
{
	char szCmdLine[150] = "C:\\Users\\Administrator\\Desktop\\OS Program\\";
	strcat(szCmdLine,Process_ID);
	
	
	STARTUPINFO si;
	ZeroMemory(reinterpret_cast<void*>(&si),sizeof(si));
	si.cb=sizeof(si);
	PROCESS_INFORMATION pi;
	
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

HANDLE MakeSharedFile()
{
	HANDLE hMapping = CreateFileMapping(
	    INVALID_HANDLE_VALUE,
	    NULL,
	    PAGE_READWRITE,
	    0,
	    160,
	    "Product_Space");
	if(hMapping != INVALID_HANDLE_VALUE)
	{
		LPVOID pData = MapViewOfFile(
		    hMapping,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0);
		if(pData != NULL)
		{
			ZeroMemory(pData,sizeof(160));
		}
		UnmapViewOfFile(pData);
	}
	return (hMapping);
}

int main(int argc,char* argv[])
{
	char Producer_Name[20] = "Producer.exe";
	char Customer_Name[20] = "Customer.exe";
	int Process_Num = 0;
	Process_Num = Producer_Num + Customer_Num;
	HANDLE Process[Process_Num];
	
	
	HANDLE hMapping = MakeSharedFile();
	
	HANDLE idle = CreateSemaphore(
	    NULL,
		3,
		3,
		"idle");
	
	HANDLE product = CreateSemaphore(
	    NULL,
		0,
		3,
		"product");
	
	HANDLE mutex = CreateMutex(
	    NULL,
		FALSE,
		"mutex");
	
	for(int i =0;i<Producer_Num;i++)
    {
    	HANDLE Producer = StartClone(Producer_Name);
    	Process[i] = Producer;
    	
	}    
    
	for(int i=0;i<Customer_Num;i++)
    {
	    HANDLE Customer = StartClone(Customer_Name);
	    Process[i+Producer_Num] = Customer;
	    
	}    
    
	
	WaitForMultipleObjects(
	    Process_Num,
		Process,
		TRUE,
		INFINITE);
	
	for(int i=0;i<Process_Num;i++)
	    CloseHandle(Process[i]);
	CloseHandle(hMapping);
	CloseHandle(idle);
	CloseHandle(product);
	CloseHandle(mutex);
	printf("MainProgram exit \n");
	return 0 ;
 } 
