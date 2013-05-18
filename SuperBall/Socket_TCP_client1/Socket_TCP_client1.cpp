// Socket_TCP_client1.cpp : Defines the entry point for the console application.
//


#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <cstdio>


/*

Message format:

vx float\0

vy float\0

ra float\0

*/


int main(int argc, char **argv)
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[32];
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);


    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(23);


    connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    recv(sock, buffer, sizeof(buffer), 0);

	printf("Data received: %s",&buffer);

	buffer[0]==' ';
	buffer[1]=='\0';
	int retval;
	do
	{
		retval = send(sock, "vx 1245.65\0", 11, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"


	//Sleep(1000);

	
	do
	{
		retval = send(sock, "vy 5689.0\0", 10, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"

	//Sleep(1000);

	
	do
	{
		retval = send(sock, "ra 34\0", 6, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"

	//Sleep(1000);

	
	do
	{
		retval = send(sock, "ra 5\0", 5, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"


	do
	{
		retval = send(sock, "Bye\0", 4, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"

	char* s;
	scanf("%s", &s);

    closesocket(sock);
    WSACleanup();
    return 0;

}