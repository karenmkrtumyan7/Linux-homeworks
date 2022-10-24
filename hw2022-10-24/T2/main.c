#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char isNumber(char *text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(isdigit(text[j]))
            continue;

        return 0;
    }
    return 1;
}

int main (int argc, char* argv[]) {
	if (argc < 2) return 1;

	if (!strcmp(argv[1], "save")) {
		int fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1) {
			perror(argv[2]);
			return 1;
		}

		char decimal[32];
		scanf("%s", decimal);
		while(isNumber(decimal)) {
			int decimal_int = atoi(decimal);
			write(fd, &decimal_int, sizeof(decimal_int));
			scanf("%s", decimal);
		}
		close(fd);
	}

	if (!strcmp(argv[1], "print")) {
		int fd = open(argv[2], O_RDONLY);
		if (fd == -1) {
			perror(argv[2]);
			return 1;
		}
		int num;
		while(read(fd, &num, sizeof(num)) > 0) {
			printf("%d\n", num);
		}
		close(fd);
	}
	return 0;
}
