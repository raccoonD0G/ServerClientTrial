#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "iostream"
#include "WinSock2.h"

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != 0)
	{
		std::cout << "Winsock Init Error" << std::endl;
		exit(-1);
	}

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "Socket Error" << std::endl;
		exit(-1);
	}

	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = PF_INET;
	ListenSockAddr.sin_addr.s_addr = inet_addr("192.168.0.5");
	ListenSockAddr.sin_port = htons(32000);

	Result = connect(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	if (Result == SOCKET_ERROR)
	{
		std::cout << "Connect Error " << GetLastError() << std::endl;
		exit(-1);
	}

	char Buffer[1024] = { 0, };
	recv(ListenSocket, Buffer, 1024, 0);
	std::cout << "Server Send : " << Buffer << std::endl;

	send(ListenSocket, Buffer, strlen(Buffer), 0);

	closesocket(ListenSocket);

	WSACleanup();
	return 0;
}