#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* func(void *p) {
	printf("Hi!\n");
	usleep(1000000);
}

int main() {
	pthread_attr_t attr;
	pthread_t thread;
	int ret;

	ret = pthread_attr_init(&attr);
	if (ret) {
		printf("Failed on attribute initialization.\n");
		return 1;
	}

	usleep(1000000);
	ret = pthread_create(&thread, &attr, func, NULL);
	if (ret) {
		printf("Fail on thread create\n");
		return 2;
	}

	pthread_join(thread, NULL);
	return 0;
}
