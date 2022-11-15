#include "env.h"

/**
 * bin_env - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: int
 */
int bin_env(int __attribute_maybe_unused__ argc,
	char __attribute_maybe_unused__ *argv[], char __attribute_maybe_unused__ *env[])
{
	unsigned int i = 0;

	for (i = 0; environ[i]; i++)
	{
		_print(environ[i], _STDIO_H), _print("\n", _STDIO_H);
	}
	return (0);
}


/**
 * bin_setenv - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: int
 */
int bin_setenv(int __attribute_maybe_unused__ argc,
	char __attribute_maybe_unused__ *argv[], char __attribute_maybe_unused__ *env[])
{
	int res;

	/* check */
	if (argc < 3)
		return (8);
	res = _setenv(argv[1], argv[2], 1);
	if (res != 0)
		return (-1);
	return (0);
}

/**
 * bin_unsetenv - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: int
 */
int bin_unsetenv(int __attribute_maybe_unused__ argc,
	char __attribute_maybe_unused__ *argv[], char __attribute_maybe_unused__ *env[])
{
	int res;

	/* check */
	if (argc < 2)
		return (8);
	res = _unsetenv(argv[1]);
	if (res != 0)
		return (-1);
	return (0);
}
