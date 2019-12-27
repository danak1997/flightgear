//
// Created by duni on 20/12/2019.
//

#include <netinet/in.h>
#include <unistd.h>
#include "OpenServerCommand.h"
#include <iostream>
#include <thread>
#include "parseBufferToSymbleTable.h"
#include "Maps.h"

void connectServer(int port) {
    int serverFd, newSocket, readValue;
    struct sockaddr_in socketAddress;
    int optionNumber = 1;
    int addressLength = sizeof(socketAddress);
    char buffer1[1] = {0};
    string bufferWithLine = "";
    char* message;

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

    cout << "accepting clients" << endl;
    if ((newSocket = accept(serverFd, (struct sockaddr *)&socketAddress, (socklen_t*)&addressLength)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout << "client connected, listen for messages" << endl;
    bool printOnce = true;
    int index = 0;
    int countCommas = 0;
    map<string, pair<float, string>>::iterator it;
    auto* parseBufferToSymbolTable1 = new parseBufferToSymbolTable();
        while (read(newSocket, buffer1, 1)) {
            char currChar = buffer1[0];
            if (currChar != '\n') {
                bufferWithLine += buffer1[0];
            } else{
              parseBufferToSymbolTable1->parseBufferAnsSymbolTables(bufferWithLine);
              bufferWithLine = "";
              for ( it = Maps::symbolTableSimToClient.begin(); it != Maps::symbolTableSimToClient.end(); it++ )
              {
                string sim = it->second.second;
                float value = Maps::xmlMap[sim];
                it->second.first = value;
              }
            }

        }
}

int OpenServerCommand::execute(vector<string> params) {
    int port = stoi(params[1]);
    cout << port << endl;
    this->threadServer = thread(connectServer, port);
    cout << "end OpenServerCommand" << endl;

    return 2;
}