#include <stdio.h>
#include <WinSock2.h>

#include "../WSASock.h"

#include <string.h>

int main(void) {
    initialize();
    struct addrinfo* result = NULL;
    struct addrinfo* addres = NULL;

    struct addrinfo hint;
    ZeroMemory(&hint, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;

    if(getaddrinfo("26.251.63.164", PORT, &hint, &result) != 0) {
        printf("getaddinfo failed, %d", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    }

    addres = result;

    printf("Creating socket...\n");

    SOCKET sock = INVALID_SOCKET;
    int con;
    sock = socket(addres->ai_family, addres->ai_socktype, addres->ai_protocol);

    printf("Connecting %s:%s...\n", "26.251.63.164", PORT);

    con = connect(sock, addres->ai_addr, (int)addres->ai_addrlen);

    freeaddrinfo(result);

    if(con != 0) {
        printf("connect Error : %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    }

    if(sock == INVALID_SOCKET) {
        printf("INVALID SOCKET, %d\n", WSAGetLastError());
        WSACleanup();
        system("pause");
        return 1;
    }

    printf("Sending data...\n");
    char recvbuff[255];
    char buffer[255];
    do {
        printf("\n>> ");
        gets(buffer);
        if(strcmp(buffer, "exit")) {
            const char* msg = buffer;
            int iRes = sendData(sock, msg);
            if(iRes == SOCKET_ERROR) {
                printf("SOCK ERROR, %d", WSAGetLastError());
                closesocket(sock);
                WSACleanup();
                system("pause");
                return 1;
            }
        }
        int resp = recv(sock, recvbuff, 255, 0);
        if(resp > 0) {
            fputs("Data recived: ", stdout);
            fputs(recvbuff, stdout);
        }
    } while (buffer != "exit");

    printf("Listening server response...\n");
    
    

    int shutdownres;

    shutdownres = shutdown(sock, SD_SEND);

    if (shutdownres == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 1;
    }

    reciveData(sock, recvbuff, 255);
    closesocket(sock);
    WSACleanup();
    system("pause");
    return 0;
}
