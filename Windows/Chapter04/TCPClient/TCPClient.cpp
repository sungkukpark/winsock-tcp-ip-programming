#include "..\..\Common.h"

char *SERVERIP = (char *)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE    512

int main(int argc, char *argv[])
{
	int retval;

	// 紐?뱁 ?몄媛 ??쇰㈃ IP 二쇱濡 ?ъ?
	if (argc > 1) SERVERIP = argv[1];

	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ?耳 ???
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ?곗댄??듭? ?ъ⑺ 蹂?
	char buf[BUFSIZE + 1];
	int len;

	// ?踰? ?곗댄??듭
	while (1) {
		// ?곗댄????
		printf("\n[蹂대??곗댄? ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 臾몄 ?嫄?
		len = (int)strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// ?곗댄?蹂대닿린
		retval = send(sock, buf, (int)strlen(buf), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		printf("[TCP ?대쇱댁명? %d諛?댄몃? 蹂대?듬??\n", retval);

		// ?곗댄?諛湲?
		retval = recv(sock, buf, retval, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 諛? ?곗댄?異??
		buf[retval] = '\0';
		printf("[TCP ?대쇱댁명? %d諛?댄몃? 諛??듬??\n", retval);
		printf("[諛? ?곗댄? %s\n", buf);
	}

	// ?耳 ?リ린
	closesocket(sock);

	// ?? 醫猷
	WSACleanup();
	return 0;
}
