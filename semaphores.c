#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


#define SEM_NAME "/mysem"


void father(sem_t *sem) {
	usleep(5 * 1000000);
	printf("father: posting on the semaphore.\n");
	sem_post(sem);
}

void son() {
	sem_t *sem = sem_open(SEM_NAME, O_RDWR);
	printf("son: Waiting for semaphore to be released...\n");
	sem_wait(sem);
	printf("son: got it!\n");
}

int main() {
	printf("Creating a named semaphore %s\n", SEM_NAME);
	sem_t *mysem = sem_open(SEM_NAME, O_CREAT, 0644, 0);
	if (!mysem) {
		perror("Could not create semaphore: ");
		exit(12);
	}

	int pid = fork();
	if (pid == 0) {
		son();
	} else {
		father(mysem);
		waitpid(pid, NULL, 0);
	}
	sem_unlink(SEM_NAME);
}
