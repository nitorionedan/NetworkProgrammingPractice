/*
@brief		�l�b�g���[�N�v���O���~���O�̗��K
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
	// �l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ȃ�
	case WSASYSNOTREADY:
		std::cout << "WSASYSNOTREADY\n";
		break;

	// �v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
	case WSAVERNOTSUPPORTED:
		std::cout << "WSAVERNOTSUPPORTED\n";
		break;

	// �u���b�L���O����̎��s���ł��邩�A 
	// �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
	case WSAEINPROGRESS:
		std::cout << "WSAEINPROGRESS\n";
		break;
	
	// winsock�������ł���ő�v���Z�X���ɒB����
	case WSAEPROCLIM:
		std::cout << "WSAERRORCLIM\n";
		break;

	// �������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
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

	/* TCP�N���C�A���g����̐ڑ��v����҂Ă��� ���@�p��ɂł��܂���i���j*/
	listen(sock0, 5);

	/* TCP�N���C�A���g����̐ڑ��v�����󂯕t���� */
	len = sizeof(client);
	sock = accept(sock0, (sockaddr*)&client, &len);

	/* submitting 5 characters to the aim */
	send(sock, "Hello TCP/IP World!", 5, 0);

	/* finish */
	Finalize(&sock);
	return 0;
}