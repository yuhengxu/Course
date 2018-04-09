#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<sys/shm.h>

#define SEM_KEY 225
#define SHM_KEY 75

//信号量标号
#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

/*
struct sembuf{
    short sem_num;   //信号量集合中要操作的信号量的索引
    short sem_op;   //信号量的操作值
    short sem_flg;  //访问标志
}sem_op;
*/
struct sembuf sem_op;

void P(int sem_id, int sem_num)
{
    sem_op.sem_num = sem_num;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

void V(int sem_id, int sem_num)
{
    sem_op.sem_num = sem_num;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

int main()
{
    size_t size = 20;   
    time_t now = 0; 
    int sem_id = semget(SEM_KEY, 3, IPC_CREAT |0660);
    int shm_id = shmget(SHM_KEY, size,IPC_CREAT | 0666);
    void* addr = shmat(shm_id, NULL, 0);
    int* pint = (int *)addr;
    
    for(int i = 0; i < 6; i++)
    {
        //随机等待一段时间
        sleep(rand() % 5);
        //对信号量EMPTY,MUTEX进行P操作
        P(sem_id, SEM_EMPTY);
        P(sem_id, SEM_MUTEX);
        printf("生产者————");

        //添加数据时间
        now = time(NULL);
        printf("时间:%02d:%02d:%02d\t", localtime(&now)->tm_hour, localtime(&now)->tm_min, localtime(&now)->tm_sec);
        //添加数据
        int data = rand() % 5 + 1;
        printf("添加数据:%d\t", data);
        int put = *pint;
        *(pint + put * 4 + 8) = data;
        if(++put > 2)put = 0;
        *pint = put;
        printf("缓存空间:%d %d %d\n",*(pint + 8),*(pint + 12),*(pint + 16));

        //对信号量FULL,MUTEX进行V操作，唤醒消费者
        V(sem_id, SEM_FULL);
        V(sem_id, SEM_MUTEX);
    }

    //将共享段与进程解除链接
    shmdt(addr);
    return 0;
}