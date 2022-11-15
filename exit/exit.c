#include "exit.h"

/**
 * bin_exit - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * @env: array of char environment variables
 * Return: int
 */
int bin_exit(int __attribute_maybe_unused__ argc,
	char __attribute_maybe_unused__ *argv[], char __attribute_maybe_unused__ *env[])
{
	int ex_code;

	if (argc <= 1)
		exit(EXIT_SUCCESS);
	if (!argv[1])
		exit(EXIT_SUCCESS);
	/* convert arg to int, unsafe */
	ex_code = _atoi(argv[1]);
	exit(ex_code);
}
