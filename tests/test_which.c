#include "../which/which.h"

/**
 * main - tests the various functions in _which proram
 * Return void
 */
int main(void)
{
	printf("orig: %s\n", getenv("PATH"));
	printf("mine: %s\n", _getenv("PATH"));
  printf("orig: %s\n", getenv("USER"));
	printf("mine: %s\n", _getenv("USER"));
  printf("orig: %s\n", getenv("NULL"));
	printf("mine: %s\n", _getenv("NULL"));
  printf("orig: %s\n", getenv("OLDPWD"));
	printf("mine: %s\n", _getenv("OLDPWD"));
  printf("orig: %s\n", getenv("GNOME_TERMINAL_SERVICE"));
	printf("mine: %s\n", _getenv("GNOME_TERMINAL_SERVICE"));
	printf("%s is a valid path\n", _which("/path"));
	printf("%s is a valid path\n", _which(".path"));
	printf("%s is a valid path\n", _which("path"));
	printf("%s is a valid path\n", _which("ls"));
	return (0);
}