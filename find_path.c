#include "shell.h"

/**
 * path_finder - Function that acts as an interface for functions that
 * will be able to find the full path of a program.
 * @command: Represents a command. For example ls, echo, pwd, etc.
 *
 * Return: Upon sucess a string with the full path of the program.
 * for example /bin/ls, /bin/echo, etc. Otherwise returns NULL.
 */

char *path_finder(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *directory;

	index = find_path(str);
	path_tokens = tokenize_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_directories(path_tokens, command);
	if (directory == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	double_free(path_tokens);

	return (constructed);
}


/**
 * find_path - Function that finds the index of an environmental variable.
 * @str: Environmental variable that needs to be found.
 * Return: Index of the environmental variable upon success.
 * And -1 if otherwise.
 */

int find_path(char *str)
{
	int x;
	int len;
	int y;

	len = str_len(str);
	for (x = 0; environ[x] != NULL; x++)
	{
		for (y = 0; y < len; y++)
		{
			if (environ[x][y] != str[y])
				break;
		}
		if (y == len && environ[x][y] == '=')
			return (x);
	}
	return (-1);
}

/**
 * tokenize_path - Function that separates a string representing paths
 * as an array of strings contining the path directories.
 * @index: Index of the path in the environment variables.
 * @str: string to separate and tokenize.
 *
 * Return: A NULL terminated array of pointer to strings upon success.
 * Otherwise returns NULL. Note!: Do not forget to free alocated
 * memory on receiving function or when possible.
 */

char **tokenize_path(int index, char *str)
{
	char *env_var;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = str_len(str);
	token_count = 0;
	env_var = environ[index] + (len + 1);
	path_tokens = token_interface(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * search_directories - Looks through directories stored in path_tokens for a
 * specific file. aka commmand.
 * @path_tokens: A pointer to an array of strings representing the different
 * paths contained in the PATH environmental varible.
 * @command: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 *
 * Return: Upon success, string with the upper most directory containing
 * the command file. If otherwise, returns NULL.
 */

char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cwd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

/**
 * build_path - Function that combines two strings.
 * one representing the path directory and another, the command file.
 * @directory: Represents a directory in the path.
 * @command: Represents a file in a directory of the path.
 *
 * Return: Upon success a string representing the full path of a command.
 * If Otherwise, returns NULL.
 */

char *build_path(char *directory, char *command)
{
	int x, y;
	int dir_len;
	int command_len;
	int len;
	char *built;

	if (directory == NULL || command == NULL)
		return (NULL);
	dir_len = str_len(directory) + 1;
	command_len = str_len(command) + 1;
	len = dir_len + command_len;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (x = 0; x < len; x++)
	{
		for (y = 0; directory[y] != '\0'; y++, i++)
			built[x] = directory[y];
		built[x] = '/';
		x++;
		for (y = 0; command[y] != '\0'; y++, x++)
			built[x] = command[y];
	}
	built[--x] = '\0';
	return (built);
}
