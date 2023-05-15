#include "shell.h"

/**
 * my_strtok - Function that tokenizes a string
 * @str: The string to be tokenized
 * @delim: The delimeter
 *
 * Return: Token
 */

char *my_strtok(char *str, const char *delim);
void my_input(char *input);

char *my_strtok(char *str, const char *delim)
{
	char *ptr = NULL;

	if (str != NULL)
		ptr = str;

	if (ptr == NULL)
		return (NULL);

	char *token = ptr;
	char *delim_ptr;

	for (; *ptr != '\0'; ptr++)
	{
		delim_ptr = (char *)delim;
		while (*delim_ptr != '\0')
		{
			if (*ptr == *delim_ptr)
			{
				*ptr = '\0';
				ptr++;
				return (token);
			}
			delim_ptr++;
		}
	}

	ptr = NULL;
	return (token);
}

/**
 * my_input - Function that stores the token
 * @input: The input
 *
 */

void my_input(char *input)
{
	char **tokens = NULL;
	int token_count = 0;
	char *token = my_strtok(input, " \t\n");

	while (token != NULL)
	{
		token_count++;
		char **temp = malloc(sizeof(char *) * token_count);

		if (temp == NULL)

		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		memcpy(temp, tokens, (token_count - 1) * sizeof(char *));
		temp[token_count - 1] = token;
		free(tokens);
		tokens = temp;
		token = my_strtok(NULL, " \t\n");
	}

	for (int i = 0; i < token_count; i++)
	{
		printf("Token %d: %s\n", i, tokens[i]);
	}

	free(tokens);
}
