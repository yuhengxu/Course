#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("mytime: missing operand\n");
        printf("Usage: mytime <FILE> [OPTION]\n");
        return 0;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Fork process failed!\n");
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    if (pid == 0)
    {
        int error = execv(argv[1], &argv[1]);
		if (error == -1)
		{
			printf("Execute \"%s\" failed!\n", argv[1]);
			return 1;
		}
        return 0;
    }

    waitpid(pid, NULL, 0);
    gettimeofday(&end, NULL);
    int t = (end.tv_sec - start.tv_sec) * 1000
             + (end.tv_usec - start.tv_usec) / 1000;
    printf("\nTime: %d ms\n", t);
    return 0;
}
