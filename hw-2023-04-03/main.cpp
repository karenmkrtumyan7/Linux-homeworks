#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main() {
    const int BUFFER_SIZE = 10;
    const int NUM_ITEMS = 100;

    int empty = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
    int full = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
    int mutex = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
    semctl(empty, 0, SETVAL, BUFFER_SIZE);
    semctl(full, 0, SETVAL, 0);
    semctl(mutex, 0, SETVAL, 1);

    int shmid = shmget(1, BUFFER_SIZE * sizeof(int), IPC_CREAT | 0644);
    int *buffer = (int*) shmat(shmid, NULL, 0);

    if (fork() == 0) {
        int item = 0;
        for (int i = 0; i < NUM_ITEMS; i++) {
            struct sembuf semops[2] = { {0, -1}, {1, -1} };
            semop(empty, &semops[0], 1);
            semop(mutex, &semops[1], 1);
            
            buffer[i % BUFFER_SIZE] = item;
            std::cout << "Produced: " << item << '\n';
            item++;
            
            semctl(mutex, 0, SETVAL, 1);
            semctl(full, 0, SETVAL, 1);
        }
        exit(0);
    }

    if (fork() == 0) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            struct sembuf semops[2] = { {2, -1}, {3, -1} };
            semop(full, &semops[0], 1);
            semop(mutex, &semops[1], 1);
            
            std::cout << "Consumed: " << buffer[i % BUFFER_SIZE] << '\n';
            
            semctl(mutex, 0, SETVAL, 1);
            semctl(empty, 0, SETVAL, 1);
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    shmdt(buffer);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(empty, 0, IPC_RMID, 0);
    semctl(full, 0, IPC_RMID, 0);
    semctl(mutex, 0, IPC_RMID, 0);

    return 0;
}

