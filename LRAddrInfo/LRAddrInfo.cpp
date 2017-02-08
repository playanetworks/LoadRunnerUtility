// LRAddrInfo.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#include "LRAddrInfo.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)  // #define _CRT_SECURE_NO_WARNINGS

LRADDRINFO_API int LRAddrInfo(const char* hostname, const char* service, char* ip_addr,int size)
{
	WSADATA wsaData;
	int iResult;

	DWORD dwRetVal;
	
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	struct sockaddr_in* sockaddr_ipv4;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	dwRetVal = getaddrinfo(hostname, service, &hints, &result);
	if (dwRetVal != 0)
	{
		printf("getaddrinfo failed with error: %d\n", dwRetVal);
		WSACleanup();
		return 2;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		sockaddr_ipv4 = (struct sockaddr_in*) ptr->ai_addr;

		strncpy(ip_addr, inet_ntoa(sockaddr_ipv4->sin_addr), size * sizeof(char));
		//strncpy_s(ip_addr, 16, inet_ntoa(sockaddr_ipv4->sin_addr), 16);
		//strcpy(ip_addr, inet_ntoa(sockaddr_ipv4->sin_addr)); 		
	}

    return 0;
}
