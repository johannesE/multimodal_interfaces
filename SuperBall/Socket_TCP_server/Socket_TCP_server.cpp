#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")



int main(int argc, char **argv)
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKET csock;
    SOCKADDR_IN sin;
    SOCKADDR_IN csin;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);


    sin.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(23);


    bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    listen(sock, 0);


    while(1)
    {
        int sinsize = sizeof(csin);
        if((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET)
        {
            send(csock, "Hello world!\r\n", 14, 0);
            closesocket(csock);
        }
    }
    /* On devrait faire closesocket(sock); puis WSACleanup(); mais puisqu'on a entré une boucle infinie ... */
    return 0;
}
