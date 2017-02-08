// LRReplaceApp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "LRReplace.h"
#include <stdio.h>

int main()
{
	int rc = 0;
	char str[] = "2017(:)01(:)01";
	char out[1024];

	rc = LRReplace(str, "(:)", "[-]", out, sizeof(out));
	printf("return: %d, string: %s\n", rc, out);

    return 0;
}

