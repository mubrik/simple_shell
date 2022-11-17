#include "env.h"

/**
 * bin_env - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int bin_env(int argc, __attribute__((unused)) char *argv[])
{
	unsigned int i = 0;

	if (argc < 0)
		return (INV);
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
 * Return: int
 */
int bin_setenv(int argc, char *argv[])
{

	/* check */
	if (argc < 3)
		return (ANV);
	return (_setenv(argv[1], argv[2], 1));
}

/**
 * bin_unsetenv - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int bin_unsetenv(int argc, char *argv[])
{

	/* check */
	if (argc < 2)
		return (ANV);
	return (_unsetenv(argv[1]));
}
