#include <bits/stdc++.h>
#include <WinSock2.h>
#include<WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

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
	} else {
		cout << "Connected!" << endl;
	}

	while (true) {
		int n,x;
		string s;
		s="";
		cout << "nhap so phan tu: ";
		cin >> n;
		cout << endl;
		cout << "nhap cac phan tu: " << endl;
		for (int i = 0; i<n; i++){
			cin >> x;
			stringstream ss;
			ss << x;
			s = s + ss.str()+ " ";
		}
		cout << "Day so nhap vao la: " << endl;
		cout << s << endl;
		// Gui du lieu
		send(socketClient, s.c_str(), strlen(s.c_str()), 0);
		 
		char buff[32768];
		ZeroMemory(buff, 32768);
		
		// Nhan du lieu tu server
		int dataRecv = recv(socketClient, buff, 32768, 0);
		cout << "Ket qua sau khi sap xep la" << endl;
		cout << string(buff,0,dataRecv) << endl;		
	}
	closesocket(socketClient);
	WSACleanup();
}
