#include "..\..\Common.h"

int main(int argc, char *argv[])
{
	// ?? 珥湲고
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	/*----------------*/
	/* IPv4 蹂? ?곗?*/
	/*----------------*/
	// ??? IPv4 二쇱 異??
	const char *ipv4test = "147.46.114.70";
	printf("IPv4 二쇱(蹂? ?) = %s\n", ipv4test);

	// inet_pton() ?⑥ ?곗?
	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	printf("IPv4 二쇱(蹂? ?) = %#x\n", ipv4num.s_addr);

	// inet_ntop() ?⑥ ?곗?
	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	printf("IPv4 二쇱(?ㅼ 蹂? ?) = %s\n", ipv4str);
	printf("\n");

	/*----------------*/
	/* IPv6 蹂? ?곗?*/
	/*----------------*/
	// ??? IPv6 二쇱 異??
	const char *ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
	printf("IPv6 二쇱(蹂? ?) = %s\n", ipv6test);

	// inet_pton() ?⑥ ?곗?
	struct in6_addr ipv6num;
	inet_pton(AF_INET6, ipv6test, &ipv6num);
	printf("IPv6 二쇱(蹂? ?) = 0x");
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.s6_addr[i]);
	printf("\n");

	// inet_ntop() ?⑥ ?곗?
	char ipv6str[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &ipv6num, ipv6str, sizeof(ipv6str));
	printf("IPv6 二쇱(?ㅼ 蹂? ?) = %s\n", ipv6str);

	// ?? 醫猷
	WSACleanup();
	return 0;
}
