#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>

int main() {
	std::string pathname = "shm_file";
	key_t key = ftok(pathname.c_str(), 'a');

	if(key < 0) {
		std::cout << "ERROR: Cannot generate a key!!\n";
		exit(errno);
	}

	int shmid = shmget(key, 300 * sizeof(int), 0600);
	int* shared_array = (int*) shmat(shmid, NULL, 0);

	if(shared_array == (int *) -1) {
		std::cout << "ERROR: Cannot attach shared mem segment!!\n";
		exit(errno);
	}
	
	bool prime[300];

	for (int p = 2; p * p <= 300; p++) {
		if (!prime[p]) {
			for (int i = p * p; i <= 300; i+=p) {
				shared_array[p] = 1;
			}
		}
	}
	
    	
	if (shmdt(shared_array) < 0) {
		std::cout << "ERROR: Cannot detach the sh m s!!\n";
		exit(errno);
	}

	return 0;
}
