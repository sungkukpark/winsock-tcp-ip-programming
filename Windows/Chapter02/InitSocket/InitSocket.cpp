癤?include "..\..\Common.h"

int main(int argc, char* argv[])
{
	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	printf("[?由? ?? 珥湲고 ?깃났\n");

	// ?耳 ???
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[?由? ?耳 ????깃났\n");

	// ?耳 ?リ린
	closesocket(sock);

	// ?? 醫猷
	WSACleanup();
	return 0;
}
