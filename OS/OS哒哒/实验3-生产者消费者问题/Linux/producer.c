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

	int sem_id = semget(SEM_KEY, SEM_NUM, 0666);
    size_t size = 2 * sizeof(int) + DATA_NUM * sizeof(struct data);
	int shm_id = shmget(SHM_KEY, size, 0);

	for (int i = 0; i < PRODUCER_CNT; i++)
	{
		semp(sem_id, SEM_EMPTY);
		semp(sem_id, SEM_MUTEX);

        void *pBuf = shmat(shm_id, NULL, 0);
        int *pInt = pBuf;
        struct data *pData = pBuf + 2 * sizeof(int);

        int tail = pInt[1];
		strcpy(pData[tail].s, msg[i]);
		printf("Producer%d => %s   ", id, pData[tail].s);
        tail = (tail + 1) % DATA_NUM;
        pInt[1] = tail;


		for (int j = 0; j < 18; j++) printf(" ");
		printf("   ");
		for (int j = 0; j < DATA_NUM; j++)
			printf("%s ", pData[j].s);
		printf("\n");

		usleep(rand() % (PRODUCER_IN_TIME + 1) * 1000);
	    shmdt(pBuf);

		semv(sem_id, SEM_FULL);
		semv(sem_id, SEM_MUTEX);

		usleep(rand() % (PRODUCER_OUT_TIME + 1) * 1000);
	}
	return 0;
}
