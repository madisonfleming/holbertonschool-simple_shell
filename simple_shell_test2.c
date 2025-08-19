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
	ssize_t read;
	pid_t pid;
	int status;
	int interactive = isatty(1);
	char *args[100];
	int i;

(void)ac;

	while (1)
	{
		/* Display prompt only if interactive */
		if (interactive)
			printf("#cisfun$ ");
		
		/* Read input */
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (interactive)
			{
				printf("\n");
				fprintf(stderr, "%s: No such file or directory\n", av[0]);
				exit(0); /* exit loop */
			}
		}
		/* Remove newline character */
		line[strcspn(line, "\n")] = '\0';

		/* Tokenize input into args[] */
		i = 0;
		args[i] = strtok(line, " ");
		while (args[i] != NULL && i < 99)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}

		/* Ignore empty input */
		if (args[0] == NULL)
			continue;

		/* Fork child process */
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(line);
			exit(1);
		}

		if (pid == 0)
		{
			/* child process runs command */
			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(127);
			}
		}
		else
		{
			/* parent waits for child */
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return 0;
}
