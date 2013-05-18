// Socket_TCP_client1.cpp : Defines the entry point for the console application.
//


#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <cstdio>

int main(int argc, char **argv)
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[255];
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(23);


    connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    recv(sock, buffer, sizeof(buffer), 0);

	printf("Data received: %s",&buffer);
	char* s;
	scanf("%s", &s);

    closesocket(sock);
    WSACleanup();
    return 0;

}