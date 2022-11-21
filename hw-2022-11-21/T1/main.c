#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if (argc < 4) return 2;

  	int fd1[2];
	if (pipe(fd1) == -1) {
		perror("error");
		exit(2);
	}
	
	int fd2[2];
	if (pipe(fd2) == -1) {
		perror("error");
		exit(2);
	}

	if (fork() == 0) {
   		dup2(fd1[1], 1);
    		close(fd1[0]);
    		close(fd1[1]);
    		close(fd2[0]);
    		close(fd2[1]);
    		execlp(argv[1], argv[1], NULL);
		exit(2);
	}
	

	if (fork() == 0) {
    		dup2(fd1[0], 0);
    		dup2(fd2[1], 1);
    		close(fd1[0]);
    		close(fd1[1]);
    		close(fd2[0]);
    		close(fd2[1]);
    		execlp(argv[2], argv[2], NULL);
    		exit(2);
	}
	
	if (fork() == 0) {
  		dup2(fd2[0], 0);
  		close(fd1[0]);
  		close(fd1[1]);
  		close(fd2[0]);
  		close(fd2[1]);
	        execvp(argv[3], argv + 3);
  		exit(2);
	}
	
	close(fd1[0]);
  	close(fd1[1]);
  	close(fd2[0]);
  	close(fd2[1]);
	return 0;
  }
