#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int main() {
	pid_t child;

	if ((child = fork()) == 0) {
		execl("./prog1", "./prog1", NULL);
		_exit(1);
	}

	int n;
	scanf("%i", &n);
	kill(child, n);

	int status;
	wait(&status);
	if (WIFSIGNALED(status)) {
		printf("Child signal %d\n", WTERMSIG(status));
	}
	return 0;
}
