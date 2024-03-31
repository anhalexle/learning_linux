.PHONY: all clean related fifo

CC := gcc

all:
	$(CC) main.c -o main

related:
	$(CC) pipe_related_process.c -o exam

fifo:
	$(CC) consumer.c -o consumer
	$(CC) producer.c -o producer

clean:
	rm -rf main exam
