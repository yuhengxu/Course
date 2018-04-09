#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <sys/wait.h>

//数目
#define PROCS_NUM 12
#define SEM_NUM 3

//标识
#define SEM_KEY 225
#define SHM_KEY 75

//信号量标号
#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

//信号量数目
#define SEM_EMPTY_NUM 3
#define SEM_FULL_NUM 0
#define SEM_MUTEX_NUM 1


union semun sem_val;

void mainStart()
{
    printf("Mainprogram begin:\n");
}
void mainEnd()
{
    printf("Mainprogram Done!\n"); 
}

int get_shm_id()
{
    /*
    int shmget(key, size, shmflg);
    key共享内存区的标识
    shmflg为创建或打开标识
    size共享内存区的字节
    */
    size_t size = 20;
    int shm_id = shmget(SHM_KEY, size, IPC_CREAT | 0666);
    /*
    void shmat(shmid, shmadd, shmflg);
    shimid是进程调用shmget返回的共享段标识
    shmadd是给出的应附加到进程虚地址空间的地址，0表示该共享段附加到系统选择的第一个可用地址之后。若非0则附加到指定的地址上
    shmflg为允许对共享段的访问方式
    */
    void* addr = shmat(shm_id, NULL, 0);
    int* pint = (int *)addr;

    return shm_id;
}

void createChildProcess()
{
    //创建生产者进程和消费者进程
    for(int i = 0; i < 5; i++)
    {
        int child_pid = fork();
        //创建失败
        if(child_pid < 0)
        {
            printf("fork error\n");
            exit(1);
        }
        //创建成功,进入子进程上下文
        else if(child_pid == 0)
        {
            //２个生产者
            if(i == 0 || i == 1)
            {
                int err = execl("./Producer.out", 0);
                if(err < 0)
                {
                    printf("Producer error\n");
                    exit(-1);
                }
            }
            //３个消费者
            else
            {
                int err = execl("./Customer.out", 0);
                if(err < 0)
                {
                    printf("Customer error\n");
                    exit(-1);
                }
            }
        }
    }
}

void semInit(int sem_id, int sem_xx_num, int sem_xx)
{
    int rc;
    sem_val.val = sem_xx_num;
    rc=semctl(sem_id, sem_xx, SETVAL, sem_val); //返回索引为０的信号量的值送arg.val中

    if(rc == -1)
    {
        perror("main's xx error\n");
        exit(1);
    }
}

int main()
{
    mainStart();
    int shm_id = get_shm_id();
    int sem_id = semget(SEM_KEY, SEM_NUM, IPC_CREAT | 0660);    
    
    if(sem_id==-1)
    {
        perror("main's semget error");
        exit(1);
    }
    //将互斥体的值设置为１
    semInit(sem_id, SEM_MUTEX_NUM, SEM_MUTEX);
   
    //将的信号量Full值设置为0
    semInit(sem_id, SEM_FULL_NUM, SEM_FULL);
    
    //将信号量Empty的值设置为3
    semInit(sem_id, SEM_EMPTY_NUM, SEM_EMPTY);
    
    //创建5个子进程
    createChildProcess();

    //父进程等待子进程结束
    for(int i = 0; i < PROCS_NUM; i++)
    {        
        wait(0);
    }
    semctl(sem_id, 0, IPC_RMID);
	shmctl(shm_id, IPC_RMID, 0);
    mainEnd();
    return 0;
}