#include <iostream>
#include <string>
#include <pthread.h>


pthread_mutex_t printer_mutex;
pthread_cond_t printer_cond;
bool is_reserved = false;

void* print(void* arg) {
	int id = *(int*)arg;

	pthread_mutex_lock(&printer_mutex);
	while (is_reserved) {
		pthread_cond_wait(&printer_cond, &printer_mutex);
	}
	
	is_reserved = !is_reserved;
	std::cout << id << "\n";
	is_reserved = !is_reserved;
	
	pthread_mutex_unlock(&printer_mutex);
	pthread_cond_signal(&printer_cond);

	return 0;
}

int main() {
	pthread_t threads[7];
	pthread_mutex_init(&printer_mutex, NULL);
	pthread_cond_init(&printer_cond, NULL);
	int ids[5];

	for (int i = 0; i < 7; ++i) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, print, &ids[i]);
	}

	for (int i = 0; i < 7; ++i) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&printer_mutex);
	pthread_cond_destroy(&printer_cond);

  	return 0;
}

