.PHONY:
all: pthread_example clone_example

.PHONY:
clean:
	rm pthread_example clone_example -f

pthread_example: pthread.c
	gcc -g -pthread ./pthread.c -o pthread_example

clone_example: clone.c
	gcc ./clone.c -g -o clone_example

