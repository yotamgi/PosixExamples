.PHONY:
all: pthread_example clone_example sem_example shmem_example zombie_example slow_reader

.PHONY:
clean:
	rm pthread_example clone_example sem_example shmem_example \
		zombie_example slow_reader -f

pthread_example: pthread.c
	gcc -g -pthread ./pthread.c -o pthread_example

clone_example: clone.c
	gcc ./clone.c -g -o clone_example

sem_example: semaphores.c
	gcc ./semaphores.c -g -o sem_example -lpthread

shmem_example: shmem.c
	gcc ./shmem.c -g -o shmem_example -lrt

zombie_example: zombie_process.c
	gcc ./zombie_process.c -g -o zombie_example

slow_reader: slow_reader.c
	gcc ./slow_reader.c -g -o slow_reader
