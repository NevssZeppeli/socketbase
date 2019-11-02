#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() 
{
    int Socket;
	sockaddr_in addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_family = AF_INET; //тип сети
    addr.sin_port = htons (7777); //порт
    addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);

    Socket = socket(AF_INET, SOCK_STREAM, 0);
    if(Socket < 0)
    {
        perror("socket");
        exit(1);
    }

    if(connect(Socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    else
    {
        std::cout << "Connected to server!\n";
    }

    shutdown (Socket, 2);
    close(Socket);

    return 0;
}