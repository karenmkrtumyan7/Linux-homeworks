#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int convert(int decimalnum)
{
    int binarynum = 0;
    int rem, temp = 1;

    while (decimalnum!=0)
    {
        rem = decimalnum%2;
        decimalnum = decimalnum / 2;
        binarynum = binarynum + rem*temp;
        temp = temp * 10;
    }
    return binarynum;
}

unsigned numDigits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + numDigits(n / 10);
}

int main (int argc, char* argv[]) {
	if (argc < 2) return 1;
	
	if (!strcmp(argv[1], "save")) {

		int fd = open(argv[2], O_RDWR | O_CREAT, 0600);

		if (fd == -1) {
			perror(argv[2]);
			return 1;
		}

		int decimal;
		scanf("%i", &decimal);

		while(decimal != 0) { // 0 is end
			char numstr[numDigits(convert(decimal))];
		        sprintf(numstr, "%i", convert(decimal));
			write(fd, numstr, strlen(numstr));
			scanf("%i", &decimal); 
		}
		close(fd);
	}
	return 0;
}
