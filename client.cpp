#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#define PORT 0000


int Socket;

void CloseSocket(int sockfd)
{
	shutdown(sockfd, 2);
	close(sockfd);
}

void ClientHandler (int socketid, int closesocketid)
{
	std::cout << "Start speaking: " << std::endl;
	while (true)
	{
	char msg [4096];
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

void sender (int socketid, int closesocketid)
{
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

int main() 
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons (PORT); //порт
	addr.sin_family = AF_INET; //тип сети

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(Socket < 0)
	{
		perror("socket");
		exit(1);
	}

	if(connect(Socket, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}
	else
	{
		std::cout << "Connected to server!\n";
	}
	std::thread msgrequest (ClientHandler, Socket, Socket);
	msgrequest.detach();
	std::thread senderofmsg (sender, Socket, Socket);
	senderofmsg.join();
	


	return 0;
}
