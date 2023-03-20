#include <unistd.h> 
#include <stdlib.h> 
#include <iostream>
#include <sys/sem.h>
#include <vector>
#include <sys/wait.h>

#define num_of_smokers = 3

int main (int argc, char *argv []) {
    std::string str;
    std::cin >> str;

    key_t key = ftok(".", 1);
    if (key < 0) {
        perror("ftok");
        exit(errno);
    }

    int semid = semget(key, num_of_ph, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget");
        exit(errno);
    }

    for (int i = 0; i < num_of_smokers; i++) {
        if (semctl(semid, i, SETVAL, 1) < 0) {
            perror("semctl");
            exit(errno);
        }
    }
    
    struct sembuf sembuf;
    int l[3] = {"T", "P", "M"};     
    for (int i = 0; i < num_of_smokers; i++) {
        pid_t pid = fork();
          if (pid == 0) {
		  while(true) {
		  	sembuf[0].sem_op = 1;

			if (semop(semid, sembuf, 1) == -1) {
				perror("semop");
			}

			std::cout << l[i];
		  	
		  	sembuf_[1].sem_op = -1;
		  	
		  	if (semop(semid, sembuf, 1) == -1) {
				perror("semop");
			}
		  }
          }
    }
    
}

    
    
