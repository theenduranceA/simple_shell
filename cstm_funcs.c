#include "shell.h"

/**
 * _strcmp - Function that compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if strings match. -1, if Otherwise.
 */

int _strcmp(char *s1, char *s2)
{
	int x;

	if (str_len(s1) != str_len(s2))
		return (-1);
	for (x = 0; s1[x] != '\0'; x++)
	{
		if (s1[x] != s2[x])
			return (-1);
	}
	return (0);
}

/**
 * _strdup - Function that creates copy of a string
 * @src: Contains the original string
 *
 * Return: Gives back the copy of string
 */

char *_strdup(char *src)
{
	int x;
	int len;
	char *dest;

	len = str_len(src);
	dest = malloc(sizeof(char) * (len + 1));

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}

/**
 * print_str - Function that prints a string character by character.
 * @str: String to be printed. If the string is NULL it will print (null)
 * @new_line: If integer is 0 a new line will be printed.
 * If otherwise a new line will not be printed.
 *
 */

void print_str(char *str, int new_line)

{
	int x;

	if (str == NULL)
		str = "(null)";
	for (x = 0; str[x] != '\0'; x++)
		write(STDOUT_FILENO, &str[x], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * _write_char - Function that writes a character to stdout
 * @c: Character that will be written to stdout
 *
 * Return: Upon success how many characters were written.
 */

int _write_char(char c)
{
	return (write(1, &c, 1));
}
