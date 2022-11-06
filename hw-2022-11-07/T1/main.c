#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		char* resp = "No args";
		write(2, resp, strlen(resp));
		return 1;
	}


	int fd = open(argv[1], O_RDWR);
	if(fd == -1){
		perror(argv[1]);
		return 2;
 	}

	char buffer;
	dup2(fd, 1);
	while(read(fd, &buffer, sizeof(buffer))){
		if(islower(buffer)){
			lseek(fd, -1, SEEK_CUR);
			buffer = toupper(buffer);
			write(1, &buffer, 1);
		} else if(isdigit(buffer)) {
			lseek(fd, -1, SEEK_CUR);
			write(1, "_", 1);
		}
	}
	close(fd);
	return 0;
}
