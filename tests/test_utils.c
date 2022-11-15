#include "../utils/utils.h"
#include <stdio.h>
#include <string.h>
/**
 * main - tests the various functions in utils proram
 * Return void
 */
int main(void)
{
	char str[] = "l  \nls\n  -la\n k jj kk ll \n b\nbB;\t", *new, *prin;

	for (new = str; ; new = NULL)
	{
		prin = _str_tok(new, " \n");
		if (!prin)
			break;
		printf("%s\n", prin);
	}

	/* printf("orig strlen: %ld\n", strlen(str) ? strlen(str) : 0);
	printf("My strlen: %d\n", _strlen(str) ? _strlen(str) : 0);
	printf("orig dup: %s\n", strdup(str));
	printf("My dup: %s\n", _strdup(str));
	printf("orig dup len: %ld\n", strlen(strdup(str)));
	printf("My dup len: %d\n", _strlen(_strdup(str)));
	printf("orig strconcat: %s\n", strcat(strdup(str), "concat"));
	printf("My strconcat: %s\n", _strconcat(_strdup(str), "concat"));
	printf("orig strconcat len: %ld\n", strlen(strcat(strdup(str), "concat")));
	printf("My strconcat len: %d\n", _strlen(_strconcat(_strdup(str), "concat"))); */
	/* printf("%s\n", _strconcatv(str, 4, "first", "second", "third", "fourth"));
	printf("%d\n", _strlen(_strconcatv(str, 4, "first", "second", "third", "fourth")));
	printf("%ld\n", strlen(_strconcatv(str, 4, "first", "second", "third", "fourth")));
	printf("Comma occured in 'j,kd,,,sl,,l,': %d times\n", _strocr(("j,kd,,,sl,,l,"), ',')); */
	return (0);
}
