// LRAddrInfoApp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "LRAddrInfo.h"
#include <stdio.h>


int main()
{
	char ip_addr[16];
	int ret_value = 0;

	ret_value = LRAddrInfo("www.google.com", "80", ip_addr, sizeof(ip_addr));

	printf("fnLRAddrInfo: %s\n", ip_addr);

    return 0;
}

