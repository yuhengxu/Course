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
    int sem_id = semget(SEM_KEY, 3, 0660);
    int shm_id = shmget(SHM_KEY, size, 0666);

    void* addr = shmat(shm_id, NULL, 0);
    int* pint = (int *)addr;

    for(int i = 0; i < 4; i++)
    {
        //随机等待一段时间
        sleep(rand() % 5);
        //对信号量FULL，MUTEX进行P操作
        P(sem_id, SEM_FULL);
        P(sem_id, SEM_MUTEX);
        printf("消费者————");
        
        //取出数据时间
        now = time(NULL);
        printf("时间:%02d:%02d:%02d\t", localtime(&now)->tm_hour, localtime(&now)->tm_min, localtime(&now)->tm_sec);
        
        //取出数据
        int take = *(pint + 4);
        printf("取出数据:%d\t",*(pint + take * 4 + 8));
        *(pint + take * 4 + 8) = 0;
        if(++take > 2)take = 0;
        *(pint + 4) = take;
        printf("缓存空间:%d %d %d\n",*(pint + 8), *(pint + 12), *(pint + 16));
        
        //对信号量EMPTY，MUTEX进行V操作，唤醒生产者
        V(sem_id, SEM_EMPTY);
        V(sem_id, SEM_MUTEX);
    }

    //将共享段与进程之间解除连接
    shmdt(addr);
    return 0;
}