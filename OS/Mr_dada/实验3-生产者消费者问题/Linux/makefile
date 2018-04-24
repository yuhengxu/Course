all: master producer consumer
.phony: all

master: master.c header.h
	gcc master.c -o master

producer: producer.c header.h
	gcc producer.c -o producer

consumer: consumer.c header.h
	gcc consumer.c -o consumer
