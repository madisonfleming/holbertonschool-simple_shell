#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int ac, char **av, char **evp)
{
	printf("evp: %p\n", (void *)evp);
	printf("environ: %p\n", (void *)environ);

return (0);
}
