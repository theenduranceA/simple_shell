#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int ac, char **argv);
int _getline(char **lineptr, size_t n, FILE *stream);
int _atoi(char *s);
int _isdigit(char *s);
int _putchar(char c);
int _puts(char *s);
int _strlen(char *s);
int *_strdup(char *str);
char _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);

#endif
