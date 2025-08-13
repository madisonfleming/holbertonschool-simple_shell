#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
extern char **environ;

int main(void)
{
	pid_t pid;
	char *args[] = {"ls", "-l", "/tmp", NULL};
	int i;

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid == -1)
		{
			printf("Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve("/bin/ls", args, environ) == -1)
			{
				printf("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
