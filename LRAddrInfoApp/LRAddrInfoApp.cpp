// LRAddrInfoApp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

