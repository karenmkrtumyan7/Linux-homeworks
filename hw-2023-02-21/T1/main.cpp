#include <iostream>
#include <string>
#include <pthread.h>

std::string src = "";
std::string dest = "";
pthread_mutex_t mutex;

void* copy_string(void* arg) {
	int id = *(int*)arg;
	int size = src.size() / 4;
	int l = id * size;
	int r = id < 3 ? (id + 1) * size : src.size();
	std::string part = src.substr(l, r - l);

	pthread_mutex_lock(&mutex);
	dest += part;
	pthread_mutex_unlock(&mutex);

	return 0;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Invalid \n"; 
		return 1;
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[4];
	int ids[4];
	src = argv[1];

	for (int i = 0; i < 4; i++) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, copy_string, &ids[i]);
	}

	for (int i = 0; i < 4; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	std::cout << dest << "\n";
	return 0;
}
