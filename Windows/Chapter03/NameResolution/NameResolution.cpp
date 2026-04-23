#include "..\..\Common.h"

#define TESTNAME "www.google.com"

// ?硫???대? -> IPv4 二쇱
bool GetIPAddr(const char *name, struct in_addr *addr)
{
	struct hostent *ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return false;
	}
	if (ptr->h_addrtype != AF_INET)
		return false;
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return true;
}

// IPv4 二쇱 -> ?硫???대?
bool GetDomainName(struct in_addr addr, char *name, int namelen)
{
	struct hostent *ptr = gethostbyaddr((const char *)&addr,
		sizeof(addr), AF_INET);
	if (ptr == NULL) {
		err_display("gethostbyaddr()");
		return false;
	}
	if (ptr->h_addrtype != AF_INET)
		return false;
	strncpy(name, ptr->h_name, namelen);
	return true;
}

int main(int argc, char *argv[])
{
	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	printf("?硫???대?(蹂? ?) = %s\n", TESTNAME);

	// ?硫???대? -> IP 二쇱
	struct in_addr addr;
	if (GetIPAddr(TESTNAME, &addr)) {
		// ?깃났?대㈃ 寃곌낵 異??
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		printf("IP 二쇱(蹂? ?) = %s\n", str);

		// IP 二쇱 -> ?硫???대?
		char name[256];
		if (GetDomainName(addr, name, sizeof(name))) {
			// ?깃났?대㈃ 寃곌낵 異??
			printf("?硫???대?(?ㅼ 蹂? ?) = %s\n", name);
		}
	}

	// ?? 醫猷
	WSACleanup();
	return 0;
}
