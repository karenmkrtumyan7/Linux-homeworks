#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	int pid = getpid();
        printf("Id: %i\n", pid);
	while (1) sleep(10);
	return 0;
}
