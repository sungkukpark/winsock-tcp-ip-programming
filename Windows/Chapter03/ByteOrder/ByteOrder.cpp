#include "..\..\Common.h"

int main(int argc, char *argv[])
{
	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	u_short x1 = 0x1234;
	u_long  y1 = 0x12345678;
	u_short x2;
	u_long  y2;

	// ?몄ㅽ?諛?댄?-> ?ㅽ몄??諛?댄?
	printf("[?몄ㅽ?諛?댄?-> ?ㅽ몄??諛?댄?\n");
	printf("%#x -> %#x\n", x1, x2 = htons(x1));
	printf("%#x -> %#x\n", y1, y2 = htonl(y1));

	// ?ㅽ몄??諛?댄?-> ?몄ㅽ?諛?댄?
	printf("\n[?ㅽ몄??諛?댄?-> ?몄ㅽ?諛?댄?\n");
	printf("%#x -> %#x\n", x2, ntohs(x2));
	printf("%#x -> %#x\n", y2, ntohl(y2));

	// ?紐삳 ?ъ??
	printf("\n[?紐삳 ?ъ??]\n");
	printf("%#x -> %#x\n", x1, htonl(x1));

	// ?? 醫猷
	WSACleanup();
	return 0;
}
