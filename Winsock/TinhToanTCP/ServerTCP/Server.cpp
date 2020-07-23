#include<bits/stdc++.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct num {
	int a, b, tong, hieu, tich, thuong;
};

int main()
{
	// Khoi tao winsock
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData)) {
		cout << "version is not supported!";
	}

	// Phan giai ten mien phia server
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Khoi tao socket
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// Ket noi
	bind(socketServer, (SOCKADDR*)&server, sizeof(server));
	
	// Lang nghe cho doi ket noi
	listen(socketServer, SOMAXCONN);

	// Phan giai ten mien phia client
	SOCKADDR_IN client;
	int clientSize = sizeof(client);
	
	// Dong y ket noi phia client
	SOCKET socketClient = accept(socketServer, (SOCKADDR*)&client, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	num Num;
	while (true)
	{
		int dataRecv = recv(socketClient, (char*)&Num, sizeof(num),0);
		
		Num.tong = Num.a + Num.b;
		Num.hieu = Num.a - Num.b;
		Num.tich = Num.a * Num.b;
		Num.thuong = Num.a / Num.b;
		
		send(socketClient, (char*)&Num, sizeof(num), 0);

	}
	closesocket(socketServer);
	WSACleanup();

	system("pause");
	return 0;

}
