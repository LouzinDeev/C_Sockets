#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT "27015"

void initialize();


int sendData(SOCKET, const char*);

void reciveData(SOCKET, char*, int);
