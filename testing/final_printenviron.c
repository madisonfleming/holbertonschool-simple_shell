#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int ac, char **av, char **env)
{
	printf("env: %p\n", (void *)env);
	printf("environ: %p\n", (void *)environ);

return (0);
}
