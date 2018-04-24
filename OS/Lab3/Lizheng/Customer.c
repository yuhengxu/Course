#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<linux/sem.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/wait.h>

#define SEM_ID 111
#define SHM_ID 75

struct sembuf sem_op;
int sem_set_id;
void P(int index)
{
    sem_op.sem_num = index;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_set_id,&sem_op,1);
}

void V(int index)
{
    sem_op.sem_num = index;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_set_id,&sem_op,1);
}

int main()
{
    int shm_id;
    int i;
    int WaitTime;
    sem_set_id = semget(SEM_ID,3,0600);
    shm_id = shmget(SHM_ID,20,0777);
    char* addr = shmat(shm_id,0,0);
    int* pData = (int*)addr;
    
    for(i=0;i<4;i++)
    {   
        WaitTime = rand()%5;
        printf("Customer:%d WaitTime:%ds\n",getpid(),WaitTime);
        printf("----------------------\n");
        sleep(WaitTime);
        P(2);
        P(0);
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
        printf("Customer:%d take the data:%d\n",getpid(),data);
        printf("-------------------------\n");
	printf("Product_Space:%d %d %d\n",*(pData+8),*(pData+12),*(pData+16));
	printf("-------------------------\n");
        V(1);
        V(0);
    }
    shmdt(addr);
    return 0;
}
    
