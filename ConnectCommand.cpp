//
// Created by duni on 22/12/2019.
//

#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include "ConnectCommand.h"

void connectClient(int port, const char* ip) {
    int socketId = 0, readValue;
    struct sockaddr_in serverAddress;
    char buffer[1024] = {0};
    char* message = "set /controls/engines/current-engine/throttle 1";

    cout << "aaln client" << endl;

    // Create socket
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "socket creation error" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "socket created" << endl;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0) {
        cout << "invalid address" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "address converted" << endl;

    if (connect(socketId, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        cout << "connection failed" << endl;
    }

    cout << "connected" << endl;

    send(socketId, message, strlen(message), 0);

    cout << "message sent" << endl;

}

int ConnectCommand::execute(vector<string> params) {
    int port = stoi(params[2]);
    int i;
    string ip = params[1];
    const char* c = ip.c_str();
    char* newC;
    for (i = 1; i < strlen(c); i++) {
        newC[i - 1] = c[i];
    }
    newC[strlen(newC) - 1] = '\0';
    thread threadClient(connectClient, port, newC);
    
    return 3;
}