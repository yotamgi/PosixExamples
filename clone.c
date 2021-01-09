#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

#define STACK_SIZE 10000

int x = 0;

int new_stuff(void *unused) {
	printf("new_stuff: My PID is %d\n", getpid());
	x = 1;
}

int main() {
	void *new_stack = malloc(STACK_SIZE);
	printf("old_stuff: My PID is %d\n", getpid());
	printf("x is %d\n", x);
	int ret = clone(new_stuff, new_stack + STACK_SIZE - 1, CLONE_VM, NULL);
	if (ret < 0) {
		perror("");
	}
	usleep(1000000);
	printf("x is %d\n", x);
}
