#include <string.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	char **env_pointer = environ;
	size_t name_length = strlen(name);

	while (*env_pointer != NULL)
	{
		if (strncmp(*env_pointer, name, name_length) == 0 && (*env_pointer)[name_length] == '=')
		{
			return (*env_pointer + name_length + 1);
		}
		env_pointer++;
	}
return (NULL);
}

int main(void)
{
	char *value = _getenv("PATH");

	if (value)
		printf("PATH = %s\n", value);
	else
		printf("PATH not found\n");
	return (0);
}
