#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	key_t key = ftok("shm_file", 1);
 	int shm_id = shmget(key, sizeof(int), 0600 | IPC_CREAT | IPC_EXCL);
 	
	if (shm_id == -1) {
		std::cout << "ERROR: Cannot create shared mem segment!!\n";
		exit(1);
	}
	
	int *shmp = (int *) shmat(shm_id, NULL, 0);
	if (*shmp == -1) {
		perror("Failed memory attach");
		exit(1);
	}
	
	key_t sem_key = ftok(".", 2);
	
	int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);
	if (sem_id < 0) {
		perror("fail");
		exit(1);
	}
	
	semctl(sem_id, 0, SETVAL, 1);
	struct sembuf sb;
	
	for (int i = 0; i < 2; i++) {
		pid_t pid = fork();
		if (pid < 0) {
		    perror("fork fail");
		    exit(1);
		} 

		if (pid == 0) {
		    for (int j = 0; j < 10000; j++) {
			sb.sem_op = -1;
			semop(sem_id, &sb, 1);

			(*shmp)++;

			sb.sem_op = 1;
			semop(sem_id, &sb, 1);
		    }
		    exit(0);
		}
	}


	wait(NULL);
	wait(NULL);

	std::cout << (*shmp);

	shmctl(shm_id, IPC_RMID, NULL);
	semctl(sem_id, 0, IPC_RMID, 0);
}
