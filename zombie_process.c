#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pid;
	pid = fork();

	if (pid == 0) {
		// child
		usleep(10 * 1000000);
		printf("Child is dying...\n");
	} else {
		// father
		usleep(20 * 1000000);
		printf("Father is dying...\n");
		waitpid(pid, NULL, 0);
	}
}
