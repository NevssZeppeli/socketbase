#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <cstring>
#define PORT 3678


void CloseSocket(int sockfd)
{
	shutdown(sockfd, 2);
	close(sockfd);
}

void sender (int socketid, int closesocketid)
{
    std::cout << "Start speaking: " << std::endl;
    while (true)
    {
    std::string msg;
    std::getline (std::cin, msg);
    std::string exit = "Messaging stopped";
    if (msg == "/exit")
    {
        std::cout << "\n--Stop--\n";
        send (socketid, exit.c_str(), sizeof(exit), 0);
        break;
        CloseSocket (closesocketid);
    }
    send (socketid, msg.c_str(), sizeof(msg), 0);
    }
}

void ClientHandler (int socketid, int closesocketid)
{
	while (true)
	{
	char msg [1024];
	recv (socketid, msg, sizeof(msg), 0);
	std::string message = std::string(msg);
	if (message == "Messaging stopped")
	{
		std::cout << "\n--Stop--\n";
        break;
        CloseSocket (closesocketid);
	}
	std::cout << ">> " << msg << std::endl;
    }
}

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

    std::thread Handler (sender, Connector, Socket);
    Handler.detach();
    std::thread viewer (ClientHandler, Connector, Socket);
    viewer.join();
    return 0;
}
