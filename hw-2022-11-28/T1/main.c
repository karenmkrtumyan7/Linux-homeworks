#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isNumber(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}

int i;

void sighandler(int sig) {
	if (i > 0) {
		printf("\n %d signals remaining", i - 1);
		i--;
		fflush(stdout);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2 || !isNumber(argv[1]) || (i = atoi(argv[1])) < 0) {
		char* resp = "Invalid input";
		write(2, resp, strlen(resp));
		return 1;
	}

	signal(SIGINT, sighandler);
	while(i) {
		 sleep(1);
	}
	return 0;
}
