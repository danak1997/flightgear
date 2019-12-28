//
// Created by duni on 22/12/2019.
//

#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include "ConnectCommand.h"
#include "Maps.h"

void connectClient(int port, string ip) {
    int socketId = 0, readValue;
    struct sockaddr_in serverAddress;
    char buffer[1024] = {0};
    string message = "set /controls/engines/current-engine/throttle 1\r\n";
    const char* c = message.c_str();

    cout << "aaln client" << endl;

    // Create socket
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "socket creation error" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "socket created" << endl;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    const char* ipConst = ip.c_str();

    if (inet_pton(AF_INET, ipConst, &serverAddress.sin_addr) <= 0) {
        cout << "invalid address" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "address converted" << endl;

    while (connect(socketId, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
    }

    cout << "connected" << endl;
    Maps::socketId = socketId;
}

int ConnectCommand::execute(vector<string> params,bool isConditionInvoked) {
  if(isConditionInvoked) {
    int port = stoi(params[2]);
    int i;
    string ip = params[1];
    ip = ip.substr(1, ip.length() - 2);
    this->threadClient = thread(connectClient, port, ip);
  }
    return 3;
}