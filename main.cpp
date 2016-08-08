/*
@brief		ネットワークプログラミングの練習
@reference	http://www.geekpage.jp/programming/winsock/
*/


#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int Initialize(WSADATA* wsaData);
int CreateSocket(SOCKET* sock);
int SetupSocket(SOCKET* socket, sockaddr_in* addr, sockaddr_in* client);
void Finalize(SOCKET* socket);


int Initialize(WSADATA* wsaData) 
{
	if (wsaData == nullptr)	return -1;

	int err = 0;

	err = WSAStartup(MAKEWORD(2, 0), wsaData);

	if (err == 0)	return 0;

	switch (err)
	{
	// ネットワークサブシステムがネットワークへの接続を準備できない
	case WSASYSNOTREADY:
		std::cout << "WSASYSNOTREADY\n";
		break;

	// 要求されたwinsockのバージョンがサポートされていない
	case WSAVERNOTSUPPORTED:
		std::cout << "WSAVERNOTSUPPORTED\n";
		break;

	// ブロッキング操作の実行中であるか、 
	// またはサービスプロバイダがコールバック関数を処理している
	case WSAEINPROGRESS:
		std::cout << "WSAEINPROGRESS\n";
		break;
	
	// winsockが処理できる最大プロセス数に達した
	case WSAEPROCLIM:
		std::cout << "WSAERRORCLIM\n";
		break;

	// 第二引数であるlpWSAData は有効なポインタではない
	case WSAEFAULT:
		std::cout << "WSAEFAULT\n";
		break;
	}

	return -1;
}


int CreateSocket(SOCKET* sock)
{
	if (sock == nullptr)	return -1;

	*sock = socket(AF_INET, SOCK_STREAM, 0);
	if (*sock == INVALID_SOCKET)
	{
		std::cout << "error : " << WSAGetLastError() << std::endl;
		return -1;
	}

	return 0;
}


int SetupSocket(SOCKET* socket, sockaddr_in* addr, sockaddr_in* client)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(64864);
	addr->sin_addr.S_un.S_addr = INADDR_ANY;
	bind(*socket, (sockaddr*)addr, sizeof(addr));

	return 0;
}


void Finalize(SOCKET* socket)
{
	closesocket(*socket);
	WSACleanup();
}


/*---------------------------------------
Main
---------------------------------------*/
int main(int argc, char* argv[]) 
{
	WSADATA wsaData;
	SOCKET sock, sock0;
	sockaddr_in addr;
	sockaddr_in client;
	int len = 0;

	/* initialization */
	if(Initialize(&wsaData) != 0)	return -1;

	/* creating the socket */
	if (CreateSocket(&sock0) != 0)	return -1;
	if (SetupSocket(&sock0, &addr, &client) != 0)	return -1;

	/* TCPクライアントからの接続要求を待てる状態 ←　英語にできません（泣）*/
	listen(sock0, 5);

	/* TCPクライアントからの接続要求を受け付ける */
	len = sizeof(client);
	sock = accept(sock0, (sockaddr*)&client, &len);

	/* submitting 5 characters to the aim */
	send(sock, "Hello TCP/IP World!", 5, 0);

	/* finish */
	Finalize(&sock);
	return 0;
}