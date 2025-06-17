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

	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));

	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "Socket Error" << std::endl;
		exit(-1);
	}

	ListenSockAddr.sin_family = PF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(32000);

	int BindResult = bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	if (BindResult == SOCKET_ERROR)
	{
		std::cout << "bind Error" << GetLastError() << std::endl;
		exit(-1);
	}

	int ListenResult = listen(ListenSocket, 5);
	if (ListenResult == SOCKET_ERROR)
	{
		std::cout << "Listen Error" << GetLastError() << std::endl;
		exit(-1);
	}

	struct sockaddr_in ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// Block Here
	SOCKET ClientSocket = accept(ListenSocket, (struct sockaddr*)&ClientSockAddr, &ClientSockAddrLength);

	const char Message[1024] = "Hello World";
	send(ClientSocket, Message, strlen(Message), 0);

	char Buffer[1024] = { 0, };
	recv(ClientSocket, Buffer, 1024, 0);

	std::cout << "Client Send : " << Buffer << std::endl;

	closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();
	return 0;
}