#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

struct num {
	int a, b, tong, hieu, tich, thuong;
};

int main()
{
	// Khoi tao winsock
	WSADATA wsa;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsa)) {
		cout << "Version is not sp!";
	}

	// Phan giai ten mien
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Khoi tao socket server
	SOCKET socketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// Ket noi
	bind(socketServer, (SOCKADDR*)&server, sizeof(server));
	// Lang nghe
	listen(socketServer, SOMAXCONN);

	// Phan giai ten mien client
	SOCKADDR_IN client;
	int clientSize = sizeof(client);
	SOCKET socketClient;
	
	num Num;

	while (true)
	{
		// Nhan du lieu tu client
		int dataRecv = recvfrom(socketServer, (char*)&Num, sizeof(num), 0, (SOCKADDR*)&client, &clientSize);
		
		Num.tong = Num.a + Num.b;
		Num.hieu = Num.a - Num.b;
		Num.tich = Num.a * Num.b;
		Num.thuong = Num.a / Num.b;

		// Gui du lieu di
		sendto(socketServer, (char*)&Num,  sizeof(num), 0, (SOCKADDR*)&client, clientSize);
	
	}

	closesocket(socketServer);
	WSACleanup();

}
