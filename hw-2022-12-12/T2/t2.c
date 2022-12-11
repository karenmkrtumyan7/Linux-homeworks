#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

pthread_mutex_t calculating;

int s;
int max = 0;
int days = 1;
int day = 1;

void calc(int l, int* arr) {
	pthread_mutex_lock(&calculating);
	
	for (int i = 0; i < l; i++) {
		s += arr[i];
	}
	
	pthread_mutex_unlock(&calculating);
}

void calc_max(int l, int* arr) {
	for (int i = 0; i < l; i++) {
		if (abs(max + arr[i]) > abs(max)) {
			max += arr[i];
			day = days;
		}
		days++;
	}
}

void* func1(void* arg) {
	int* arr = (int *) arg;
	calc(arr[0], arr + 1);
	calc_max(arr[0], arr + 1);
}


int main(int argc, char *argv[]) {
	s = atoi(argv[1]);
	int t = atoi(argv[2]);
	char path[1024];
	strcpy(path, "../T3/");
	strcat(path, argv[3]);
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Invalid");
		return 1;
	}
	
	int n;
	read(fd, &n, sizeof(n));
	int nums[n];
	int num;
	for (int i = 0; read(fd, &num, sizeof(num)) > 0; i++) {
		nums[i] = num;
	}
	
	pthread_t threads[t];
	
  	for (int i = 0; i < t; ++i) {
  		int a = i * (n / t);
  		int b = (i + 1) * (n / t);
  		
  		if (i == t - 1) 
  			b = n;
  			
  		int part[b - a];
  		part[0] = b - a;

  		memcpy(part + 1, nums + a, sizeof(int) * (b - a));
    		pthread_create(&threads[i], NULL, func1, (void*)part);
    		pthread_join(threads[i], NULL);
  	}
  	
  	printf("%i\n", s);
  	printf("%i\n", day);
	close(fd);
}
