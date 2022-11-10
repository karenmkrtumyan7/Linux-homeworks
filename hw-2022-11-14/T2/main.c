#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

int main() {
	int fd[2], result, i = 0;
	long long size;

	if (pipe(fd) != 0) {
		return 1;
	}

	while (1) {
		size = write(fd[1], "Message", 8);
		printf("%d\n", ++i);
	}
	return 0;
}
