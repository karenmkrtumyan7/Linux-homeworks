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

	char name[1024];
	char filename[1024];
	char buffer[1024];

	int i = 0;
	int n = read(fd, buffer, sizeof(buffer));
	while(i < n) {
		if (!isspace(buffer[i])) {
			name[i] = buffer[i];
		} else {
			buffer[i] = '\0';
			name[i] = '\0';
			break;
		}
		i++;
	}
	
	i = 0;
	while(i < n) {
		if (!isspace(buffer[i])) {
			filename[i] = buffer[i];
		} else {
			buffer[i] = '\0';
			filename[i] = '\0';
			break;
		}
		i++;
	}


	if (fork() == 0) {
		int fd2 = open(filename, O_CREAT | O_WRONLY, 0666);
		dup2(fd2, 0);
		execvp(name, argv); // when i treid to keep pointer to argumentss compiler return error
		exit(0);
	}
	wait(NULL);
	return 0;
}
