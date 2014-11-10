/***
* Utils.c
* Author - Nurgaliev Ildar
*
*Purpose:
*       This contains commonly used methods
*
****/
#include <ctype.h>
#include <string.h>

/**
* trims strings from both sides
*/
void trim(char *s)
{
	/* delete spaces and tabs in the start of the row */
	int i, j;
	for (i = 0; (s[i] == ' ') || (s[i] == '\t'); i++);
	if (i > 0)
	{
		for (j = 0; j < strlen(s); j++)
		{
			s[j] = s[j + i];
		}
		s[j] = '\0';
	}

	/* delete spaces and tabs in the end of the row */
	for (i = strlen(s) - 1; (s[i] == ' ') || (s[i] == '\t'); i--);
	if (i < (strlen(s) - 1))
	{
		s[i + 1] = '\0';
	}
}

void tolower_string(char *p){
	for ( ; *p; ++p) *p = tolower(*p);
}
