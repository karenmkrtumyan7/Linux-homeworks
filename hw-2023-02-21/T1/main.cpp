#include <iostream>
#include <string>
#include <pthread.h>

std::string src = "";
std::string dest = "";
std::string dest_parts[4];
pthread_mutex_t mutex;
bool finished[4] = { false };

void* copy_string(void* arg) {
    int id = *(int*)arg;
    int size = src.size() / 4;
    int l = id * size;
    int r = id < 3 ? (id + 1) * size : src.size();
    std::string part = src.substr(l, r - l);

    pthread_mutex_lock(&mutex);
    dest_parts[id] = part;
    finished[id] = true;
    pthread_mutex_unlock(&mutex);

    return 0;
}

void* combine_strings(void* arg) {
    while (!finished[0] || !finished[1] || !finished[2] || !finished[3]) {}

    for (int i = 0; i < 4; i++) {
        dest += dest_parts[i];
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Invalid \n"; 
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[5];
    int ids[4];
    src = argv[1];

    pthread_create(&threads[4], NULL, combine_strings, NULL);

    for (int i = 0; i < 4; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, copy_string, &ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_join(threads[4], NULL);
    pthread_mutex_destroy(&mutex);

    std::cout << dest << "\n";
    return 0;
}

