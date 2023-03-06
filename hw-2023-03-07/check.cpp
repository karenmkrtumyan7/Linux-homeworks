#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Invalid Args \n";
		return 1;
	}
	
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
		perror("shmat");
		exit(errno);
	}
	
	shared_array[atoi(argv[1])] ? std::cout << "Yes" : std::cout << "No";
        
        if(shmdt(shared_array) < 0) {
		std::cout << "ERROR: Cannot detach the sh m s!!\n";
		exit(errno);
	}
        
        return 0;
}
