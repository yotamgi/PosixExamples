#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>


#define MYSHMEM_SIZE 100
#define MYSHMEM_NAME "myshmem"

void father(int shfd) {
	char *shbuf = mmap(NULL, MYSHMEM_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, shfd, 0);

	if (!shbuf) {
		perror("Could not mmap on father");
		exit(3);
	}
	while (1) {
		for (int i=0; i<100; i++) {
			*(int *)shbuf = i;
			usleep(1000);
		}
	}
}

void son(int shfd) {
	char *shbuf = mmap(NULL, MYSHMEM_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, shfd, 0);

	if (!shbuf) {
		perror("Could not mmap on son");
		exit(3);
	}
	for (int i=0; i<100; i++) {
		usleep(500000);
		printf("%d\n", *(int *)shbuf);
	}
}

int main() {
	int fd = shm_open(MYSHMEM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror("Could not create shared memory");
		exit(1);
	}
	if (ftruncate(fd, MYSHMEM_SIZE) != 0) {
		perror("Could not ftruncate");
		exit(2);
	}

	int pid = fork();
	if (pid == 0) {
		son(fd);
	} else {
		father(fd);
	}

	shm_unlink(MYSHMEM_NAME);

	return 0;
}
