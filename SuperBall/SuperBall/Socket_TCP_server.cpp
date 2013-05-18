#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <cstdio>

#include <pthread.h>

#include "SuperBall.h";

/*

Message format: (strings)

vx float\0

vy float\0

ra float\0

*/






void* threadsTask( void* ptVoid)
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKET sockFrom;
    SOCKADDR_IN sin;
    SOCKADDR_IN from;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
	char Buffer[32];
	char subbuff[32];


    sin.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(23);


    bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    listen(sock, 0);

	

	int retval;
	bool connected=false;
	bool acceptNewConnections = true;

    while(acceptNewConnections)
    {
		connected=false;
		printf("The server socket on the addres %d listens on port %d.\n", sin.sin_addr.s_addr,  sin.sin_port);
        int sinsize = sizeof(from);
        if((sockFrom = accept(sock, (SOCKADDR *)&from, &sinsize)) != INVALID_SOCKET)
        {
			printf("Server: accepted connection from %d, port %d\n", inet_ntoa(from.sin_addr),  htons(from.sin_port)) ;
            retval = send(sockFrom, "Hello world!\r\n", 14, 0);

			//retval = send(msgsock, Buffer, sizeof(Buffer), 0)
			if (retval == SOCKET_ERROR)
			{
					fprintf(stderr,"Server: send() failed: error %d\n", WSAGetLastError());
					connected=false;
			}
			else connected=true;

			int stringsLength;
			float parameter;

			while(connected)
			{

				retval = recv(sockFrom, Buffer, sizeof(Buffer), 0);
				//-----------

				if (retval == SOCKET_ERROR)
				{
					fprintf(stderr,"Server: recv() failed: error %d. Disconnecting.\n", WSAGetLastError());
					closesocket(sockFrom);
					connected=false;
				}
				else
				{
					printf("Server: message received from %s, port %d: %s\n", inet_ntoa(from.sin_addr), htons(from.sin_port), Buffer);
				}

				stringsLength = (unsigned)strlen(Buffer);
				if(stringsLength < 4) 
				{
					printf("Server: received string is shorter that 4 chars, disconnecting.\n");
					closesocket(sockFrom);
					connected=false;
					acceptNewConnections = false;
				}

				memcpy( subbuff, &Buffer[3], stringsLength );
				subbuff[stringsLength] = '\0';

				printf("	Server: string value of the parameter: %s\n",subbuff);

				parameter = (float)(atof(subbuff));

				switch (Buffer[0])
				{
					case 'v': 
					{
						if(Buffer[1]=='x') { printf("Server: update for vx: %f\n",parameter);  SuperBall::update_vX(parameter); }
						
						else if(Buffer[1]=='y') { printf("Server: update for vy: %f\n",parameter);  SuperBall::update_vY(parameter); }
						
						break;
					}
					case 'r':
					{
						 printf("Server: update for the radius: %f\n",parameter); 
						 SuperBall::updateRadius(parameter);
						 break;
					}
				}

				retval = send(sockFrom, "Ack\0", 4, 0);
				if (retval == SOCKET_ERROR)
				{
					fprintf(stderr,"Server: send() failed: error %d. Disconnecting.\n", WSAGetLastError());
					closesocket(sockFrom);
					connected=false;
				}
				else
				{
					printf("Server: Ack sent\n");
				}
			}
            
        }


		
    }
	

	closesocket(sock);
	printf("Server: closesocket()\n");
	
	WSACleanup();

	printf("\nServer: Bye.\n");

	//scanf("%s",&subbuff);

    return 0;
}

//should be declared as extern in other files that use it:
void start_the_Thread_with_the_Socket_TCP_server()
{
	
	pthread_t thread;


	printf("Launching the thread\n");
    pthread_create(&thread, NULL, threadsTask, NULL);
    printf("Thread launched.\n");


	/* Wait for thread to finish */
   //pthread_join(thread, NULL);
    
}