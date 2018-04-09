#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/sem.h>


#define NUM_PROCS 5
#define SEM_ID 225
#define FILE_NAME "./1.txt"
#define DELAY 400000


union semun {
    int val;                    //SETVAL的值
    struct semid_ds *buf;       //为IPC_STAT和IPC_SET的缓冲区
    ushort *arrary[];           //为获得GETALL和设置的SETALL信号量的数组
}arg;


//子进程互斥写文件的通用函数
void update_file(int sem_set_id, char * file_name_path, int number)
{
    /*
    struct sembuf{
        ushort sem_num;         信号量集合中要操作的信号量索引
        short sem_op;           信号量的操作值，可为正、负、0
        short sem_flg;          访问标志(IPC_NOWAIT或SEM_UNDO)
    };
    */
    struct sembuf sem_op;
    FILE* file;

    //以下操作相当于P操作，申请写文件
    /*
    进程通过semop对信号量集合中的一个或多个信号量执行P/V操作
    int semop(int semid, struct sembuf * sops, unsigned nsops);
    semid是进程调用semget后返回的信号量集合的标识符， 
    sops是用户提供的操作信号量的模板数组的指针，
    nsops是一次需要进行的操作的数组sembef中的元素数
    */
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);

    //向文件进行写操作，写入的是进程的标识
    file = fopen(file_name_path, "a");
    if(file)
    {
        fprintf(file, "%d\n", number);
        printf("%d\n", number);
        fclose(file);
    }
    else printf("Open file %s error!\n", file_name_path);

    //以下操作相当于V操作，释放文件的使用权
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

//子进程准备写文件的通用函数
void do_child_loop(int sem_set_id, char *file_name_path)
{
    pid_t pid = getpid();       //得到本进程的标识
    update_file(sem_set_id, file_name_path, pid);
}

int main(int argc, char** argv)
{
    int sem_set_id, child_pid;
    union semun sem_val;
    int rc;

    //创建一个信号量集合,标识为225,该集合只有一个信号量
    /*
    int semget(key_t, int nsems, int semflg);
    key为用户进程指定的信号量集合的关键字
    nsems为信号量集合中的信号量数
    semflg为规定的创建和打开标志
    */
    sem_set_id = semget(SEM_ID, 1, IPC_CREAT|0600);

    if(sem_set_id == -1)
    {
        perror("main's semget error\n");
        exit(1);
    }

    //把该信号量的值设置为１
    /*
    对信号量执行控制操作
    int semctl(int semid, int semnum, int cmd, union semun arg);
    semid是信号量集合的标识
    semnum是信号量索引
    cmd是要执行的操作命令
    arg用于设置或返回信号量信息的参数，它是一个指向联合semun的指针，
    ｃｍｄ取值SETVAL：设置索引为semnum的信号量的值为arg.val
    */
    sem_val.val = 1;
    rc = semctl(sem_set_id, 0, SETVAL, sem_val);
    if(rc == -1)
    {
        perror("main setctl error\n");
        exit(1);
    }

    //建立一些子进程，相互竞争并互斥的向文件中写
    for(int i = 0; i < NUM_PROCS; i++)
    {
        child_pid = fork();
        switch(child_pid)
        {
            case -1:
                perror("fork()\n");
                exit(1);
            case 0:
                do_child_loop(sem_set_id, FILE_NAME);
                exit(0);
            default: break;
        }
    }//创建子进程结束

    //父进程等待子进程结束
    for(int i = 0; i < NUM_PROCS; i++)
    {
        int child_status;
        wait(&child_status);
    }

    printf("main is done.\n");
    fflush(stdout);

    return 0;
}