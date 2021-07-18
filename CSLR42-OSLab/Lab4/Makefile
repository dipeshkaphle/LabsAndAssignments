CFLAGS=-lm -lrt
CC=gcc

all: prod cons1 cons2

prod: producer.c
	$(CC) $(CFLAGS) -o prod producer.c

cons1: prod consumer1.c
	$(CC) $(CFLAGS) -o cons1 consumer1.c

cons2: prod consumer2.c
	$(CC) $(CFLAGS) -o cons2 consumer2.c

unlink_shm: unlink_mem.c prod
	$(CC) $(CFLAGS) -o unlink_shm unlink_mem.c

clean: unlink_shm
	rm prod cons1 cons2
	./unlink_shm
	rm ./unlink_shm
