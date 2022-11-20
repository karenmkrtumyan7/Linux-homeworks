#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if (argc < 4) return 2;

  	int fd[2];
	if (pipe(fd) == -1) {
		perror("error");
		exit(2);
	}

	if (fork() == 0) {
		sleep(1);
   		dup2(fd[1], 1);
    		close(fd[0]);
    		close(fd[1]);
    		execlp(argv[1], argv[1], NULL);
		exit(2);
	}
	

	if (fork() == 0) {
		sleep(2);
    		dup2(fd[0], 0);
    		dup2(fd[1], 1);
    		close(fd[0]);
    		close(fd[1]);
    		execlp(argv[2], argv[2], NULL);
    		exit(2);
	}
  		
	if (fork() == 0) {
		sleep(3);
    		dup2(fd[0], 0);
    		execvp(argv[3], argv + 4);
    		close(fd[0]);
		close(fd[1]);
    		exit(2);
	}	
	
	close(fd[0]);
        close(fd[1]);
	return 0;
  }
