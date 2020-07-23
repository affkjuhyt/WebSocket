#include <iostream>
#include <WinSock2.h>
#include<WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

struct num {
	int a, b, tong, hieu, tich, thuong;
};

int main()
{
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData)) {
		cout << "version is not supported!";
	}

	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");


	SOCKET socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (connect(socketClient, (SOCKADDR*)&server, sizeof(server)) != 0) {
		cout << "Can't connect to server!";
		closesocket(socketClient);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Connected!" << endl;
	}

	num mess;
	num Num;

	while (true)
	{
		int so1, so2;
		cout << "Nhap so thu 1: ";
		cin >> so1;
		cout << "Nhap so thu 2: ";
		cin >> so2;

		mess.a = so1;
		mess.b = so2;
		
		send(socketClient, (char*)&mess, sizeof(num), 0);


		int dataRecv = recv(socketClient, (char*)&Num, sizeof(num), 0);

		cout<<"Tong 2 so: "<<Num.tong<<endl;
		cout<<"Hieu 2 so: "<<Num.hieu<<endl;
		cout<<"Tich 2 so: "<<Num.tich<<endl;
		cout<<"Thuong 2 so: "<<Num.thuong<<endl;
		
	}
	closesocket(socketClient);
	WSACleanup();

}

