#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 7777

void CloseSocket(int sockfd)
{
	shutdown(sockfd, 2);
	close(sockfd);
}

int main() 
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons (PORT); //порт
	addr.sin_family = AF_INET; //тип сети

	int Socket = socket(AF_INET, SOCK_STREAM, IPROTO_TCP);
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
	CloseSocket(Socket);
}
