#include <stdio.h>
#include "str.h"

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		printf("%d %d\n", string_length(argv[i]), num_digits(argv[i]));
	}
	return 0;
}
