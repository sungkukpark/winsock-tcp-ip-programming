癤?*** ?ш린?遺????梨? 紐⑤ ???? 怨듯듭쇰? ?ы⑦???ъ⑺? 肄??대? ***/

#define _CRT_SECURE_NO_WARNINGS // 援ы C ?⑥ ?ъ?? 寃쎄? ?湲?
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 援ы ?耳 API ?ъ?? 寃쎄? ?湲?

#include <winsock2.h> // ??2 硫???ㅻ
#include <ws2tcpip.h> // ??2 ????ㅻ

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib 留??

// ?耳 ?⑥ ?ㅻ? 異??? 醫猷
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ?耳 ?⑥ ?ㅻ? 異??
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ?耳 ?⑥ ?ㅻ? 異??
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[?ㅻ?] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

/*** ?ш린源吏媛 ??梨? 紐⑤ ???? 怨듯듭쇰? ?ы⑦???ъ⑺? 肄??대? ***/
/*** 2???댄? ???ㅼ Common.h瑜??ы⑦? 諛⑹?쇰? ??肄?瑜??ъ⑺??  ***/

#define SERVERPORT 9000
#define BUFSIZE    512

// TCP ?踰(IPv4)
DWORD WINAPI TCPServer4(LPVOID arg)
{
	int retval;

	// ?耳 ???
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ?곗댄??듭? ?ъ⑺ 蹂?
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ??? ?대쇱댁명??蹂?異??
		printf("\n[TCP ?踰] ?대쇱댁명???: IP 二쇱=%s, ?ы?踰??%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// ?대쇱댁명몄 ?곗댄??듭
		while (1) {
			// ?곗댄?諛湲?
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 諛? ?곗댄?異??
			buf[retval] = '\0';
			printf("%s", buf);
		}

		// ?耳 ?リ린
		closesocket(client_sock);
		printf("[TCP ?踰] ?대쇱댁명?醫猷: IP 二쇱=%s, ?ы?踰??%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}

	// ?耳 ?リ린
	closesocket(listen_sock);
	return 0;
}

// TCP ?踰(IPv6)
DWORD WINAPI TCPServer6(LPVOID arg)
{
	int retval;

	// ?耳 ???
	SOCKET listen_sock = socket(AF_INET6, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// ????ㅽ? ??? [Windows? 爰쇱???(湲곕낯媛). UNIX/Linux? OS留???ㅻ?]
	int no = 1;
	setsockopt(listen_sock, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&no, sizeof(no));

	// bind()
	struct sockaddr_in6 serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin6_family = AF_INET6;
	serveraddr.sin6_addr = in6addr_any;
	serveraddr.sin6_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ?곗댄??듭? ?ъ⑺ 蹂?
	SOCKET client_sock;
	struct sockaddr_in6 clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ??? ?대쇱댁명??蹂?異??
		char ipaddr[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &clientaddr.sin6_addr, ipaddr, sizeof(ipaddr));
		printf("\n[TCP ?踰] ?대쇱댁명???: IP 二쇱=%s, ?ы?踰??%d\n",
			ipaddr, ntohs(clientaddr.sin6_port));

		// ?대쇱댁명몄 ?곗댄??듭
		while (1) {
			// ?곗댄?諛湲?
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 諛? ?곗댄?異??
			buf[retval] = '\0';
			printf("%s", buf);
		}

		// ?耳 ?リ린
		closesocket(client_sock);
		printf("[TCP ?踰] ?대쇱댁명?醫猷: IP 二쇱=%s, ?ы?踰??%d\n",
			ipaddr, ntohs(clientaddr.sin6_port));
	}

	// ?耳 ?リ린
	closesocket(listen_sock);
	return 0;
}

int main(int argc, char* argv[])
{
	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 硫?곗ㅻ?瑜??댁⑺??? 媛? ?踰瑜???? 援щ???
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, TCPServer4, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, TCPServer6, NULL, 0, NULL);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	// ?? 醫猷
	WSACleanup();
	return 0;
}
