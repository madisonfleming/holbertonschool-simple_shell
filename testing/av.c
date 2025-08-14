#include <stdio.h>

int main(__attribute__((unused)) int ac, char **av)
{
	char **current = av;

	while (*current != NULL)
	{
		printf("%s\n", *current);
		current++;
	}
	return (0);
}
