//
// Created by duni on 20/12/2019.
//

#include <netinet/in.h>
#include <unistd.h>
#include "OpenServerCommand.h"
#include <iostream>
#include <thread>

void connectServer(int port) {
    int serverFd, newSocket, readValue;
    struct sockaddr_in socketAddress;
    int optionNumber = 1;
    int addressLength = sizeof(socketAddress);
    char buffer[1024] = {0};
    char* message;

    cout << "aaln" << endl;

    // Create socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optionNumber, sizeof(optionNumber))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *)&socketAddress, sizeof(socketAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((newSocket = accept(serverFd, (struct sockaddr *)&socketAddress, (socklen_t*)&addressLength)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout << "start" << endl;
    while(read(newSocket, buffer, 1024)) {
        cout << buffer << endl;
    }
}

int OpenServerCommand::execute(vector<string> params) {
    int port = stoi(params[1]);
    cout << port << endl;

    thread treadServer(connectServer, port);
    cout << "end" << endl;
    //treadServer.join();
    while(1){}

    return 2;
}