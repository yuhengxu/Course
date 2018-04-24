#ifndef PRODUCERCONSUMER_HEADER_H
#define PRODUCERCONSUMER_HEADER_H

#define PRODUCER_NAME "producer"
#define CONSUMER_NAME "consumer"

#define PRODUCER_NUM 2
#define PRODUCER_CNT 12
#define CONSUMER_NUM 3
#define CONSUMER_CNT 8

#define SEM_KEY 2018
#define SEM_NUM 3
#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

#define SHM_KEY 2019

struct data
{
	char s[8];
};
#define DATA_NUM 6

char *msg[12] = {
	"dataA", "dataB", "dataC", "dataD",
	"dataE", "dataF", "dataG", "dataH",
	"dataI", "dataJ", "dataK", "dataL"
};

#define PRODUCER_IN_TIME 500
#define PRODUCER_OUT_TIME 800
#define CONSUMER_IN_TIME 1500
#define CONSUMER_OUT_TIME 2000

#endif //PRODUCERCONSUMER_HEADER_H
