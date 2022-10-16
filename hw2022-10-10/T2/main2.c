#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	for (int i = 2; i < argc; i++) {
		if(fork() == 0) {
			execlp(argv[1], argv[1], argv[i], NULL);
			return 127;
		}
	}
	wait(NULL);
	return 0;
}
