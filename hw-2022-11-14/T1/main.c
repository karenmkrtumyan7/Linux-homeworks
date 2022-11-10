#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
	if (argc < 5) return 1;

	int fd1 = open(argv[2], O_RDONLY);

	if (fd1 == -1) {
		perror(argv[2]);
		exit(2);
	}
	
	int fd[2];
	if (pipe(fd) == -1) {
		perror(NULL);
		exit(2);
	}


	if (fork() == 0) {
		dup2(fd1, 0);
		dup2(fd[1], 1);
		close(fd1);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[1], argv[1], NULL);
	}

	int status;
    	wait(&status);
  
   	 if (WIFEXITED(status) && !WEXITSTATUS(status)) {
      	 	int fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);

		if (fd2 == -1) {
			perror(argv[4]);
			exit(1);
		}

		dup2(fd[0], 0);
		dup2(fd2, 1);
		close(fd1);
		close(fd2);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[3], argv[3], NULL);
		exit(2);
    	 }
	return 0;
}
