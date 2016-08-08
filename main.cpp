/*
@brief		ネットワークプログラミングの練習
@reference	http://www.geekpage.jp/programming/winsock/
*/


#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int Initialize(WSADATA* wsaData = nullptr);
int CreateSocket(SOCKET* sock = nullptr);
void Finalize();


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


void Finalize() 
{
	WSACleanup();
}


/*---------------------------------------
Main
---------------------------------------*/
int main(int argc, char* argv[]) 
{
	/* initialization */
	WSADATA wsaData;
	if(Initialize(&wsaData) != 0)	return -1;

	/* creating the socket */
	SOCKET sock;
	if (CreateSocket(&sock) != 0)	return -1;

	/* finish */
	Finalize();
	return 0;
}