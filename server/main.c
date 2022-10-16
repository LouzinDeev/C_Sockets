#include <stdlib.h>
#include <WinSock2.h>
#include "../WSASock.h"

int main() {
    initialize();
    struct addrinfo *result = NULL, hint;
    ZeroMemory(&hint, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_flags = AI_PASSIVE;
    printf("Geting addres...\n");
    int res = getaddrinfo(NULL, PORT, &hint, &result);
    if(res != 0) {
        printf("Getaddr error, error: %d", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    } else {
        printf("Succes\n");
    }
    printf("Creating socket...\n");
    SOCKET listener = INVALID_SOCKET;

    listener = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(listener == INVALID_SOCKET) {
        printf("Invalid socket, error: %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    } else {
        printf("Socket Created\n");
    }
    printf("binding socket...\n");

    res = bind(listener, result->ai_addr, (int)result->ai_addrlen);
    if(res != 0) {
        printf("error: %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    } else {
        printf("Succes\n");
    }

    printf("listening...\n");
    if(listen(listener, SOMAXCONN ) == SOCKET_ERROR) {
        printf("error: %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    }
    printf("Creating client connection...\n");
    SOCKET ClientSocket;
    int counter;

    ClientSocket = accept(listener, NULL, NULL);
        if(ClientSocket== INVALID_SOCKET) {
            printf("error: %d\n", WSAGetLastError());
            WSACleanup();
            system("pause");
            return 1;
        }

    printf("Reciving data...\n");
    char recvbuff[255];
    reciveData(ClientSocket, recvbuff, 255);

    res = shutdown(ClientSocket, SD_SEND);
    if(res != 0) {
        printf("error: %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    }
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}