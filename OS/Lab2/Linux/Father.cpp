#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdio.h>

int main(int argc, char* argv[])
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        printf("fork succeed\n");
        char **arg = &argv[1];
        execv(argv[1], arg);
    }
    else
    {
        wait(NULL);

        gettimeofday(&end, NULL);
        time_t time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
        printf("子进程用时： %ld ms\n", time);

    }

    return 0;
}