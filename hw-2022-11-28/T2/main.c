#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

long long bits = 0;

void sigpipe_handler() {
	printf("Broken pipe!\n");
	printf("%f bytes\n", bits / (float)(8));
	exit(1);
}

int main(int argc, char* argv[]) {
  	int fd[2];
  	int write_id;
  	
	if (pipe(fd) == -1) {
		exit(2);
	}

	if ((write_id = fork()) == 0) {
		signal(SIGPIPE, sigpipe_handler);
		char* text = "Hello world";
		while(write(fd[1], text, strlen(text))) {
			bits += strlen(text);
		}
	}
	
	char text[5];
	read(fd[0], text, 5);
	printf("%s\n", text);
	kill(write_id, SIGPIPE);
	exit(0);
}
