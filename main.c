#include "shell.h"

/**
 * main - Entry point to shell
 * @ac: The argument count
 * @av: The argument vector
 *
 * Return: Always 0 (Success)
 */

int main(int ac, char **av)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t my_read = 0;
	(void)ac;
	(void)av;

	while (1)

	{
		if (my_read == -1)
			my_read = getline(&lineptr, &n, stdin);
		return (-1);

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
	}

	free(lineptr);

	return (0);
}
