#include "exit.h"

/**
 * bin_exit - main function int argc, char *argv[], char *env[]
 * @argc: argument count
 * @argv: array of char argument values
 * Return: int
 */
int bin_exit(int argc, char *argv[])
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
