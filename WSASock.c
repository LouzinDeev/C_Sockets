#include "WSASock.h"
#include <string.h>

void initialize() {
    WSADATA wsa;
    int result;
    result = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(result == 0) {
        printf("WSA Initialized\n");
    } else {
        printf("WSA Error %s\n", WSAGetLastError());
    }
}
int sendData(SOCKET sock, const char* buff) {
    int len = strlen(buff);
    len++;
    int res = send(sock, buff, len, 0);
    return res;
}

void reciveData(SOCKET sock, char* buff, int len) {
    int response;
    do {
        response = recv(sock, buff, len, 0);
        if(response > 0) {
            fputs("\nData recived: ", stdout);
            fputs(buff, stdout);
            const char* resp;
            resp = buff;
            sendData(sock, buff);
        } else if(response == 0) {
            printf("Connection closed");
        } else {
            printf("Recive failed");
        }
    } while (response > 0);
}


