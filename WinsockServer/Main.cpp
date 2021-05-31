#include <WinSock2.h>

int main()
{
	WSADATA wsaData;
	SOCKET ListeningSocket;
	SOCKET NewConnection;
	SOCKADDR_IN ServerAddr;
	SOCKADDR_IN ClientAddr;
	int Port = 5150;

	// initialize Winsock version 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// create a new socket to listen for client connection
	ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// create a SOCKADDR_IN struct to tell bind
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind: associate socket and address info
	bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	// listen client connection with 5 backlog
	listen(ListeningSocket, 5);

	int ClientAddrLen;
	// client connected, accept a connection
	NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen);

	// can do:
	// 1. call accept again to accept other client connection
	// 2. send and receive data in NewConnection

	// close socket
	closesocket(NewConnection);
	closesocket(ListeningSocket);

	// call WSACleanup to clean
	WSACleanup();
}