#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int Process_ID,WaitTime;
	Process_ID = GetCurrentProcessId();
	printf("Customer:%d start to take data\n",Process_ID);
	HANDLE hMapping = OpenFileMapping(
	    FILE_MAP_WRITE,
		FALSE,
		"Product_Space");
	LPVOID pfile = MapViewOfFile(
	    hMapping,
		FILE_MAP_WRITE,
		0,
		0,
		0);
	int* pData = reinterpret_cast<int*>(pfile);
	HANDLE Idle_Handle = OpenSemaphore(
	    SEMAPHORE_ALL_ACCESS,
		FALSE,
		"idle");
	HANDLE Mutex_Handle = OpenMutex(
	    MUTEX_ALL_ACCESS,
		FALSE,
		"mutex");
	HANDLE Product_Handle = OpenSemaphore(
	    SEMAPHORE_ALL_ACCESS,
		FALSE,
		"product");
	
	for(int i=0;i<4;i++)	
	{
	    WaitTime = rand()%5;
	    WaitTime = WaitTime*1000;
	    printf("-------------------------\n");
		printf("Customer:%d WaitTime:%dms\n",Process_ID,WaitTime);
	    printf("-------------------------\n");
		Sleep(WaitTime);
	    WaitForSingleObject(Product_Handle,INFINITE);
	    WaitForSingleObject(Mutex_Handle,INFINITE);
	    printf("Product_Space:%d %d %d\n",*(pData+8),*(pData+12),*(pData+16));
		printf("-------------------------\n");
		int index = *(pData+4);
	    printf("%d\n",index);
		int data;
		data = *(pData+index*4+8);
		*(pData+index*4+8) = 0;
	    index++;
	    if(index>2)
	        index = 0;
	    *(pData+4) = index;
	    printf("Customer:%d take the data:%d\n",Process_ID,data);
	    printf("-------------------------\n");
		printf("Product_Space:%d %d %d\n",*(pData+8),*(pData+12),*(pData+16));
		printf("-------------------------\n");
		ReleaseSemaphore(
	        Idle_Handle,
		    1,
		    NULL);
	    ReleaseMutex(Mutex_Handle);
    }
    
	CloseHandle(hMapping);
    CloseHandle(Idle_Handle);
    CloseHandle(Mutex_Handle);
    CloseHandle(Product_Handle);
    printf("Customer:%d exit\n",Process_ID);
	return 0;
}
