#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5454

int Connections[100];
int counter = 0;

int main() 
{
    int Socket, Connector;
	sockaddr_in addr;
    addr.sin_family = AF_INET; //тип сети
    addr.sin_port = htons (PORT); //порт
    addr.sin_addr.s_addr = htonl (INADDR_ANY);

    Socket = socket (AF_INET, SOCK_STREAM, 0);
    if(Socket < 0)
    {
        perror("socket");
        exit(1);
    }
    else 
    {
        std::cout << "Socket works\n";
    }
    
    if (bind (Socket, (sockaddr *)&addr, sizeof(addr)) !=0)
    {
        perror("bind");
        exit(2);
    }
    else
    {
        std::cout << "Bind works\n";
    }
    int sizeofaddr = sizeof(addr);
    listen (Socket, SOMAXCONN);

    Connector = accept(Socket, (sockaddr *)&addr, (socklen_t *)&sizeofaddr);
    if(Socket < 0)
    {
        perror("accept");
        exit(3);
    }   
    else
    {
        std::cout << "Accepted\n";
    }
    char msg[256] = "Hello, blyad";
    send (Connector, msg, sizeof(msg), 0);
    shutdown (Socket, 2);
    close(Socket);
    
    return 0;
}
