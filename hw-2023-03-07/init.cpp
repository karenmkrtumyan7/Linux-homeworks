#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <cmath>

int main() {
	std::string pathname = "shm_file";
	key_t key = ftok(pathname.c_str(), 'a');
	
	if(key < 0) {
		std::cout << "ERROR: Cannot generate a key!!\n";
		exit(errno);
	}
	
	int shmid = shmget(key, 300 * sizeof(int), IPC_CREAT | 0600);
	
	if (shmid == -1) {
		std::cout << "ERROR: Cannot create shared mem segment!!\n";	
		exit(errno);
	}
	
	int* shared_array = (int*) shmat(shmid, NULL, 0);
	if(shared_array == (int *) -1) {
		std::cout << "ERROR: Cannot attach shared mem segment!!\n";
		exit(errno);
	}
	
	for (int i = 0; i < 300; i++){
		shared_array[i] = 0;
	}
    	
    	if(shmdt(shared_array) < 0) {
		std::cout << "ERROR: Cannot detach the sh m s!!\n";
		exit(errno);
	}
	
    	return 0;
}
