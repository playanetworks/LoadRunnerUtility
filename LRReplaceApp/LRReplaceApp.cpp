// LRReplaceApp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

