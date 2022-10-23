#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
	if(argc < 3) return 1;

	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		perror(argv[1]);
		return 1;
	};

	int fd2 = open(argv[2], O_CREAT | O_RDWR, 0644);
	if (fd2 == -1) {
		perror(argv[2]);
		return 1;
	}
	char buffer;
	
	while(read(fd1, &buffer, 1)) {
		if (isdigit(buffer)) {
			buffer = 'x';
		}
		write(fd2, &buffer, 1);
	}

	close(fd1);
	close(fd2);

	return 0;

}
