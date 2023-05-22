#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include "colorprint.hpp"

#define MAX_BUFFER_SIZE 1024

int totalRequests = 0;
pthread_mutex_t totalRequestsMutex;
pthread_cond_t totalRequestsCond;

void* handleClient(void* arg) {
    int clientSocket = *((int*)arg);

    char buffer[MAX_BUFFER_SIZE] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            break;
        }

        std::string request(buffer);
        std::string response;

        if (request == "shutdown") {
            response = "Server shutdown";
            break;
        } else {
            pthread_mutex_lock(&totalRequestsMutex);
            totalRequests++;
            if (totalRequests % 5 == 0) {
                pthread_cond_signal(&totalRequestsCond);
            }
            pthread_mutex_unlock(&totalRequestsMutex);

            response = "Request received";
        }

        send(clientSocket, response.c_str(), response.length(), 0);
    }

    close(clientSocket);

    return NULL;
}

void* printTotalRequests(void*) {
    while (true) {
        pthread_mutex_lock(&totalRequestsMutex);
        pthread_cond_wait(&totalRequestsCond, &totalRequestsMutex);
        pthread_mutex_unlock(&totalRequestsMutex);

        Painter p(std::cout, {"requests"}, {});
        p.printColoredLine("Requests processed: " + std::to_string(totalRequests));
    }
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed create server socket." << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        close(serverSocket);
        return 1;
    }

    pthread_t printThread;
    pthread_create(&printThread, NULL, printTotalRequests, NULL);

    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            close(serverSocket);
            return 1;
        }
    }

    close(serverSocket);

    return 0;
}

