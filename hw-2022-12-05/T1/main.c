#include <pthread.h>
#include <stdio.h>

void* printId(void* arg){
	printf("%i\n", *(int *)arg);
	return 0;
}

int main() {
	pthread_t t1, t2, t3, t4;
	int args[] = {0, 1, 2, 3};

	pthread_create(&t1, NULL, printId, &args[0]);
	pthread_create(&t2, NULL, printId, &args[1]);
	pthread_create(&t3, NULL, printId, &args[2]);
	pthread_create(&t4, NULL, printId, &args[3]);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	printf("Finished");
	return 0;
}
