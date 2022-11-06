#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDWR);
	if(fd == -1){
		perror(argv[1]);
		return 2;
 	}

	char name[4096];
	char filename[2040];

	char buffer;
	int i = 0;
	while(read(fd, &buffer, sizeof(buffer))) {
		if (!isspace(buffer)) {
			name[i] = buffer;
		} else {
			break;
		}
		i++;
	}

	i = 0;
	while(read(fd, &buffer, sizeof(buffer))) {
		if (!isspace(buffer)) {
			filename[i] = buffer;
		} else {
			break;
		}
		i++;
	}


	if (fork() == 0) {
		int fd2 = open(filename, O_CREAT | O_WRONLY, 0666);
		dup2(fd2, 0);
		execvp(name, argv);
		exit(0);
	}
	wait(NULL);
	return 0;
}
