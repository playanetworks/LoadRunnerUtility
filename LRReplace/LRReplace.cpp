// LRReplace.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "LRReplace.h"

#pragma warning(disable:4996)  // #define _CRT_SECURE_NO_WARNINGS

char *strReplace(const char *src, const char *from, const char *to);

/*
*
* Description:
*    Find and replace text within a LoadRunner string.
*
* Parameters:
*    in   (in)  - pointer to LoadRunner Parameter Name
*    from (in)  - pointer to text top search for
*    to   (in)  - pointer to text to use as replacement
*    out  (out)
*    size (in)
*
* Returns:
*    Returns an integer. 0=Error, 1=Success.
*
*/
LRREPLACE_API int LRReplace(const char *in, const char *from, const char *to, char *out, int size)
{
	int res = 0;
	char *result;

	// Do the Search and Replace
	result = strReplace(in, from, to);

	// Process results
	if (result != NULL)
	{
		strncpy(out, result, size);
		free(result);
		res = 1;
	}
	return res;
}

/*
*
* Description:
*    Find and replace text within a LoadRunner string.
*
* Parameters:
*    src (in)    - pointer to String
*    from (in)    - pointer to text top search for
*    to (in) - pointer to text to use as replacement
*
* Returns:
*    Returns an integer. 0=Error, 1=Success.
*/
char *strReplace(const char *src, const char *from, const char *to)
{
	int size;
	int fromlen;
	int tolen;

	char *dst;
	char *buffer;
	char *match;

	// Find out the lengths of the source string, text to replace, and the replacement text.
	size = strlen(src) + 1;
	fromlen = strlen(from);
	tolen = strlen(to);

	// Allocate the first chunk with enough for the original string.
	buffer = (char *)malloc(size);

	// We need to return 'buffer', so let's make a copy to mess around with.
	dst = buffer;

	// Before we begin, let's see if malloc was successful.
	if (buffer != NULL)
	{
		// Loop until no matches are found.
		for (;;)
		{
			// Try to find the search text.
			match = (char *)strstr(src, from);
			if (match != NULL)
			{
				// Found search text at location 'match'. Find out how many characters to copy up to the 'match'.
				size_t count = match - src;

				// We are going to realloc, and for that we will need a temporary pointer for safe usage.
				char *temp;

				// Calculate the total size the string will be after the replacement is performed.
				size += tolen - fromlen;

				// Attempt to realloc memory for the new size.
				temp = (char *)realloc(buffer, size);

				if (temp == NULL)
				{
					// Attempt to realloc failed. Free the previously malloc'd memory and return with our tail between our legs.
					free(buffer);
					return NULL;
				}

				// The call to realloc was successful. But we'll want to return 'buffer' eventually, so let's point it to the memory that
				// we are now working with. And let's not forget to point to the right location in the destination as well.
				dst = temp + (dst - buffer);
				buffer = temp;

				// Copy from the source to the point where we matched. Then move the source pointer ahead by the amount we copied. 
				// And move the destination pointer ahead by the same amount.
				memmove(dst, src, count);
				src += count;
				dst += count;

				// Now copy in the replacement text 'to' at the position of the match. Adjust the source pointer by the text we replaced.
				// Adjust the destination pointer by the amount of replacement text.
				memmove(dst, to, tolen);
				src += fromlen;
				dst += tolen;
			}
			else
			{
				// Copy any remaining part of the string. This includes the null termination character.
				strcpy(dst, src);
				break;
			}
		} // End of for loop
	}
	return buffer;
}
