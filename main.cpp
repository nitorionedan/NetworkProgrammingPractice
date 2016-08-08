#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


WSADATA g_wsaData;


void Initialize(WSADATA wsaData);
void Finalize();

void Initialize(WSADATA wsaData) 
{
	g_wsaData = wsaData;
	int err = 0;

	err = WSAStartup(MAKEWORD(2, 0), &wsaData);

	if (err == 0)	return;

	switch (err)
	{
	case WSASYSNOTREADY:
		std::cout << "WSASYSNOTREADY\n";
		break;

	case WSAVERNOTSUPPORTED:
		std::cout << "WSAVERNOTSUPPORTED\n";
		break;

	case WSAEINPROGRESS:
		std::cout << "WSAEINPROGRESS\n";
		break;

	case WSAEPROCLIM:
		std::cout << "WSAERRORCLIM\n";
		break;

	case WSAEFAULT:
		std::cout << "WSAEFAULT\n";
		break;
	}
}


void Finalize() 
{
	WSACleanup();
}


int main(int argc, char* argv[]) 
{
	WSADATA wsaData;
	Initialize(wsaData);

	Finalize();
	return 0;
}