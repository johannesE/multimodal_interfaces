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

q____     ('q' followed by at least 4 spaces)

*/

// Look below at the main() method for a use sample. (Include the functions in other files by declaring them 'extern' at the beginning of the files)


SOCKET sock;

void socket_client_connect()
{
	WSADATA WSAData;
    SOCKADDR_IN sin;
    char buffer[32];
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);


    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(23);

	printf("Waiting for the server to accept new connections\n");
    int retval1 = connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    int retval2 = recv(sock, buffer, sizeof(buffer), 0);
	if(retval1 != SOCKET_ERROR && retval2 != SOCKET_ERROR) printf("Connection established\n");
}

void socket_client_updateVx(float value)
{
	int retval;
	char buffer[32];
	
	sprintf( buffer, "vx ");
	int length = sprintf( &(buffer[3]), "%f", value);
	buffer[3+length]='\0';

	do
	{
		retval = send(sock, buffer, length + 4 , 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"
}

void socket_client_updateVy(float value)
{
	int retval;
	char buffer[32];

	sprintf( buffer, "vy ");
	int length = sprintf( &(buffer[3]), "%f", value);
	buffer[3+length]='\0';

	do
	{
		retval = send(sock, buffer, length + 4 , 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"
}

	
void socket_client_updateRadius(float value)
{
	int retval;
	char buffer[32];

	sprintf( buffer, "ra ");
	int length = sprintf( &(buffer[3]), "%f", value);
	buffer[3+length]='\0';

	do
	{
		retval = send(sock, buffer, length + 4 , 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"
}


void socket_client_disconnect_only()
{
	int retval;
	char buffer[32];
	do
	{
		retval = send(sock, "Bye\0", 4, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"

    closesocket(sock);
    WSACleanup();
	printf("Connection closed.\n");
}


void socket_client_disconnect_and_send_the_Shutdown_order_to_the_server()
{
	int retval;
	char buffer[32];
	do
	{
		retval = send(sock, "q    \0", 5, 0);
		retval = recv(sock, buffer, sizeof(buffer), 0);
	} 
	while(retval == SOCKET_ERROR || (unsigned)strlen(buffer)==0 || buffer[0]=='r');  //'r' for "retransmit"

    closesocket(sock);
    WSACleanup();
	printf("Connection closed.\n");
}



int main(int argc, char **argv)
{
	
	socket_client_connect();

	socket_client_updateVx(1.23456f);
	socket_client_updateVy(-0.7654322f);
	socket_client_updateRadius(36.0f);

	socket_client_disconnect_only();


	socket_client_connect();
	socket_client_disconnect_and_send_the_Shutdown_order_to_the_server();


	char* s;
	scanf("%s", &s);
}
