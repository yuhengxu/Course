#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<linux/sem.h>



#define SEM_ID 111
#define SHM_ID 75
int main()
{
    int sem_set_id,shm_id;
    int i;
    pid_t pid;
    struct shmid_ds * buf;
    union semun sem_val;
    int rc;
    sem_set_id = semget(SEM_ID,3,IPC_CREAT|0600);
    if(sem_set_id == -1)
    {
        printf("main's semget error\n");
        exit(1);
    }
    
    sem_val.val = 1;                            //Mutex index:0
    rc = semctl(sem_set_id,0,SETVAL,sem_val);
    if(rc == -1)
    {
        printf("mutex create error\n");
        exit(1);
    }
    
    sem_val.val = 3;
    rc = semctl(sem_set_id,1,SETVAL,sem_val);    //Idle index:1
    if(rc == -1)
    {         
        printf("Idle_sem create error\n");
        exit(1);
    }
    
    sem_val.val = 0;
    rc = semctl(sem_set_id,2,SETVAL,sem_val);     //Product index:2
    if(rc == -1)
    {
        printf("Product_sem create error\n");
        exit(1);
    }

    shm_id = shmget(SHM_ID,20,0777|IPC_CREAT);
    char* addr = shmat(shm_id,0,0);
    int* pData = (int*)addr;
    for(i=0;i<5;i++)
        *(pData+i*4) = 0;
        
    for(i=0;i<5;i++)
    {
        if((pid = fork()) < 0)
        {
            printf("fork error\n");
            exit(1);
        }
        if(pid == 0&&i < 2)
        {
            if(execl("/home/tos/Desktop/Producer","Producer",0) < 0)
            {
                printf("execl error\n");
                exit(-1);
            }
         }
        else 
        if(pid == 0&&i >= 2)
        {
            if(execl("/home/tos/Desktop/Customer","Customer",0) < 0)
            {
                printf("execl error\n");
                exit(-1);
            }
        }
    }
    
    for(i=0;i<5;i++)
        wait(0);        
    
    semctl(sem_set_id,0,IPC_RMID,sem_val);
    shmctl(shm_id,IPC_RMID,buf);
    printf("MainProgram Exit\n");
    return 0;
}

