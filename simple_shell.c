#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int status;
	int interactive = isatty(1);
(void)ac;

while (1)
{
        /* Display prompt only if interactive */
	if (interactive)
		printf("#cisfun$ ");

	if (getline(&line, &len, stdin) == -1)
	{
	   
		if (interactive)
		{
			printf("\n");
			fprintf(stderr, "%s: No such file or directory\n", av[0]);
			exit(0);
		}
	}
	line[strcspn(line, "\n")] = '\0';

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(line);
		exit(1);
	}

	if (pid == 0)
	{
      
		char *args[100];
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			free(line);
			exit(127);
		}
	}
	else
	{ 
		waitpid(pid, &status, 0);
	}
}

return 0;
}
