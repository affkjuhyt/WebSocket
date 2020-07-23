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
	// Khoi tao winsock
	WSADATA wsa;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsa)) {
		cout << "version is not sp!";
	}

	// Phan giai ten mien
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int serverSize = sizeof(server);
	// Khoi tao socket
	SOCKET socketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	num mess;
	num Num;

	while (true) {
		
		int so1, so2;
		cout << "Nhap so thu 1: ";
		cin >> so1;
		cout << "Nhap so thu 2: ";
		cin >> so2;

		mess.a = so1;
		mess.b = so2;
		
		// Send to giong send o 4 tham so dau, 2 tham so sau la giong doan yeu cau connect cua tcp
		sendto(socketClient, (char*)&mess, sizeof(num), 0, (SOCKADDR*)&server, serverSize);
		// Nhan du lieu tu server tra ve cung the
		int dataRecv = recvfrom(socketClient, (char*)&Num, sizeof(num), 0, (SOCKADDR*)&server, &serverSize);

		cout<<"Tong 2 so: "<<Num.tong<<endl;
		cout<<"Hieu 2 so: "<<Num.hieu<<endl;
		cout<<"Tich 2 so: "<<Num.tich<<endl;
		cout<<"Thuong 2 so: "<<Num.thuong<<endl;
	}
	
	closesocket(socketClient);
	WSACleanup();
}
    

