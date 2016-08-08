/*
@brief		�l�b�g���[�N�v���O���~���O�̗��K
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