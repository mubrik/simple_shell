# Simple Shell Project

## Description

Recreating a simpler version of the popular bash shell `/bin/sh`

## Files

- `main.c`: The root of the project, Holds the main function.
- `main.h`: The main header ile for the project.

## Compiling

- To run the program : `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c ./which/*.c ./utils/*.c ./token/*.c -o myshell`

## Testing

You can run various tests for different functions
To test the functions in each program use:

- `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ./utils/*.c ./tests/test_utils.c -o test_utils`
- `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ./utils/*.c ./which/*.c ./tests/test_which.c -o test_which`

All compiled specific test programs can be run with valgrind to test for leaks e.g:
`valgrind ./test_which`
