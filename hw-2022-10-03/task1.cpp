#include <stdio.h>
#include <cstring>

int main(int argc, char* argv[]){
	int l;
	int r;
	int res;
	sscanf(argv[1], "%d", &l);
	sscanf(argv[3], "%d", &r);

	if (!strcmp(argv[2], "+")){
		res = l + r;
		printf("%d\n", res);
	} else if (!strcmp(argv[2], "x")){ //with * not work
		res = l * r;
		printf("%d\n", res);
	}
	return 0;
}
