#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	srand(time(0));
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int k = atoi(argv[3]);
	
	int fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1) {
		perror(argv[1]);
		return 2;
 	}
 	
	write(fd, &n, sizeof(n));
	int buffer;
	for (int i = 0; i < n; i++) {
		buffer = m + (rand() % (k - m + 1));
		write(fd, &buffer, sizeof(buffer));
	}
	return 0;
}
