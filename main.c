#include "shell.h"

/**
 * main - Entry point to shell
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	const char *prompt = "$ ";
	char *my_lineptr = NULL;
	size_t n = 0;
	int my_count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, prompt, strlen(prompt));

		my_count = getline(&my_lineptr, &n, stdin);
		if (my_count == -1)
		{
			if (feof(stdin))
			{
				write(STDERR_FILENO, "Howdy!!!\n", strlen("Howdy!!!\n"));
		}
			free(my_lineptr);
			return (-1);
		}

		write(STDERR_FILENO, my_lineptr, (size_t)my_count);
		free(my_lineptr);
		my_lineptr = NULL;
		n = 0;
	}

	free(my_lineptr);

	return (0);
}
