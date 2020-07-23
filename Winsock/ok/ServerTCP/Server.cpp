#include<bits/stdc++.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

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

	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(socketServer, (SOCKADDR*)&server, sizeof(server));
	listen(socketServer, SOMAXCONN);

	SOCKADDR_IN client;
	int clientSize = sizeof(client);
	SOCKET socketClient = accept(socketServer, (SOCKADDR*)&client, &clientSize);
	
	while (true) {
		char buf[32768];
		ZeroMemory(buf, 32768);
		
		int dataRecv = recv(socketClient,buf, 32768,0);
		string s1 = buf;
		int a[1000];
		
		istringstream stream(s1);
		int x,dem=0;
		while (stream>>x){
			a[dem] = x;
			dem++;
		}
		
		for (int i=0;i<dem;i++) {
			for(int j=i+1;j<dem;j++){
				if (a[i]>a[j]) {
					int tg=a[i];
					a[i]=a[j];
					a[j]=tg;
				}
			}
		}
		
		string s="";
		for (int i=0;i<dem;i++){
			stringstream ss;
			ss << a[i];
			s = s+ ss.str()+" ";
		}
		
		char const *charResult  = s.c_str();
		send(socketClient, charResult, strlen(charResult), 0);

	}
	
	closesocket(socketServer);
	WSACleanup();

	system("pause");
	return 0;

}
