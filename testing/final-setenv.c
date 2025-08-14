#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
  * _setenv - set environment variable
  * @name: string representing the name of the environment variable to be set or modified
  * @value: a string representing the value to be assigned to the environment variable
  * @overwrite: an integer flag
  * If overwrite is nonzero the function will update the value of name if it already exists
  * If overwrite is zero and name already exists, the function will not change its value
  * Return: 0 on success, -1 on error
  */
extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0;
	size_t name_length;
	char *new_variable;

	if (name == NULL || value == NULL)
		return -1;

	if (strchr(name, '=') != NULL)
		return -1;

	name_length = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, name_length) == 0 && environ [i][name_length] == '=')
		{
			if (overwrite == 0)
				return 0;

			new_variable = malloc(name_length + strlen(value) + 2);
			if (new_variable == NULL)
				return -1;
			sprintf(new_variable, "%s=%s", name, value);
			environ[i] = new_variable;
			return 0;
		}
		i++;
	}
	new_variable = malloc(name_length + strlen(value) + 2);
	if (new_variable == NULL)
		return -1;
	sprintf(new_variable, "%s=%s", name, value);

	int env_count = 0;
	char **new_environ;
	while (environ[env_count] != NULL)
	{
		new_environ = malloc((env_count + 2) * sizeof(char *));
		if (new_environ == NULL)
		{
			free(new_variable);
			return -1;
		}
		env_count++;
	}
	i = 0;
	while (i < env_count)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[env_count] = new_variable;
	new_environ[env_count + 1] = NULL;

	environ = new_environ;
return 0;
}

int main(void)
{
	_setenv("MYVARIABLE", "HELLO", 1);
	printf("%s\n", getenv("MYVARIABLE"));
	return 0;
}
