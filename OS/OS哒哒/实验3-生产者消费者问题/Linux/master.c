#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "header.h"

void showheader()
{
	char *head[] = {"Producer", "Consumer", "Buffer"};
	int width[] = {18, 18, 6 * DATA_NUM - 1};
	int num = 3;
	for (int i = 0; i < num; i++)
	{
		char fmt[10];
		sprintf(fmt, "%%-%ds", width[i]);
		printf(fmt, head[i]);
		printf("   ");
	}
	printf("\n");
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < width[i]; j++) printf("-");
		printf("   ");
	}
	printf("\n");
}

int shminit()
{
    size_t size = 2 * sizeof(int) + DATA_NUM * sizeof(struct data);
	int shm_id = shmget(SHM_KEY, size, IPC_CREAT | 0666);
	void *pBuf = shmat(shm_id, NULL, 0);
	int *pInt = pBuf;
	struct data *pData = pBuf + 2 * sizeof(int);

	pInt[0] = pInt[1] = 0;
	for (int i = 0; i < DATA_NUM; i++)
		strcpy(pData[i].s, "-----");
		
	shmdt(pBuf);
	return shm_id;
}

int seminit()
{
	int sem_id = semget(SEM_KEY, SEM_NUM, IPC_CREAT | 0660);
	semctl(sem_id, SEM_EMPTY, SETVAL, DATA_NUM);
	semctl(sem_id, SEM_FULL, SETVAL, 0);
	semctl(sem_id, SEM_MUTEX, SETVAL, 1);
	return sem_id;
}

void start(char *name, int id)
{
	if (fork() == 0)
	{
		char index[5];
		sprintf(index, "%d", id);
		int s = execl(name, name, index, NULL);
		if (s == -1)
		{
			printf("Exec %s failed!\n", name);
			exit(1);
		}
	}
}

int main(int argc, char *argv[])
{
	int shm_id = shminit();
	int sem_id = seminit();
	showheader();

	for (int i = 1; i <= PRODUCER_NUM; i++)
	{
		start(PRODUCER_NAME, i);
	}
	for (int i = 1; i <= CONSUMER_NUM; i++)
	{
		start(CONSUMER_NAME, i);
	}

	for (int i = 0; i < PRODUCER_NUM + CONSUMER_NUM; i++)
	{
		wait(NULL);
	}

	semctl(sem_id, 0, IPC_RMID);
	shmctl(shm_id, IPC_RMID, 0);
	return 0;
}
