#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "header.h"

void semp(int sem_id, ushort sem_num)
{
	struct sembuf sop = {sem_num, -1, 0};
	semop(sem_id, &sop, 1);
}

void semv(int sem_id, ushort sem_num)
{
	struct sembuf sop = {sem_num, 1, 0};
	semop(sem_id, &sop, 1);
}

int main(int argc, char *argv[])
{
	int id = 0;
	if (argc > 1) id = strtol(argv[1], NULL, 10);
	srand(time(NULL));

	int sem_id = semget(SEM_KEY, SEM_NUM, 0600);
    size_t size = 2 * sizeof(int) + DATA_NUM * sizeof(struct data);
	int shm_id = shmget(SHM_KEY, size, 0);

	for (int i = 0; i < CONSUMER_CNT; i++)
	{
		semp(sem_id, SEM_FULL);
		semp(sem_id, SEM_MUTEX);

        void *pBuf = shmat(shm_id, NULL, 0);
        int *pInt = pBuf;
        struct data *pData = pBuf + 2 * sizeof(int);
		usleep(rand() % (CONSUMER_IN_TIME + 1) * 1000);

        int head = pInt[0];
		for (int j = 0; j < 21; j++) printf(" ");
		printf("Consumer%d <= %s   ", id, pData[head].s);
		strcpy(pData[head].s, "-----");
        head = (head + 1) % DATA_NUM;
        pInt[0] = head;

		for (int j = 0; j < DATA_NUM; j++)
			printf("%s ", pData[j].s);
		printf("\n");
	    shmdt(pBuf);

		semv(sem_id, SEM_EMPTY);
		semv(sem_id, SEM_MUTEX);

		usleep(rand() % (CONSUMER_OUT_TIME + 1) * 1000);
	}
	return 0;
}
