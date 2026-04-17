//
// Created by Admin on 17.04.2026.
//
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include "unistd.h"

#include "inet.h"

int initConnection(
        struct sockaddr_in* _ServerAddr,
        int* _EPollFD,
        int* _SocketFD,
        const char* _ServerName,
        uint16_t _ServerPort
) {
    int res = EXIT_FAILURE;
    if (!initServerAddres(_ServerAddr,_ServerName, _ServerPort)) {
        if (!initDescriptors(_EPollFD, _SocketFD)) {

        }
    }

    return res;
}
