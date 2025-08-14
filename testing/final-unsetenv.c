#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int _unsetenv(const char *name)
{
	int i = 0, j,
	size_t length;

	if (name == NULL || strchr(name, '=') != NULL)
		return -1;

	length = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, length) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			j = i;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j] + 1;
				j++;
			}
			return 0;
		}
		i++;
	}
return 0;
}
