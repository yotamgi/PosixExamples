#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i;
	char c;

	for (i=0; i < 100; i++) {
		usleep(1000000);
		read(0, &c, 1);
		write(1, &c, 1);
	}
}
