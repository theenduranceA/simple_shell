#include "shell.h"

/**
 * _cd - Changes the current working directory to the parameter passed to cd.
 * if no parameter is passed it changes directory to HOME.
 * @line: A string representing the input from the user.
 */

void _cd(char *line)
{
	int index;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	param_array = token_interface(line, delim, token_count);
	if (param_array[0] == NULL)
	{
		single_free(2, param_array, line);
		return;
	}
	if (param_array[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(param_array[1], "-") == 0)
		print_str(param_array[1], 0);

	else
		chdir(param_array[1]);
	double_free(param_array);
}

/**
 * env_b - Function that prints environmental variables in the current shell.
 * @line: A string representing the input from the user.
 */

void env_b(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * u_exit - Function that exits the shell after freeing allocated resources.
 * @line: A string representing the input from the user.
 */

void u_exit(char *line)
{
	free(line);
	print_str("\n", 1);
	exit(1);
}

/**
 * check_built_ins - Finds the right function needed for execution.
 * @str: The name of the function that is needed.
 * Return: A pointer to a void function upon Success. And NULL if otherwise.
 */

void (*check_built_ins(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", u_exit},
		{"env", _env},
		{"cd", _cd},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}

/**
 * built_in - Functin that checks for builtin functions.
 * @command: An array of all the arguments passed to the shell.
 * @line: A string representing the input from the user.
 * Return: 0 If function is found, -1 If otherwise.
 */

int built_in(char **command, char *line)
{
	void (*build)(char *);

	build = check_built_ins(command[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		double_free(command);
	build(line);
	return (0);
}
