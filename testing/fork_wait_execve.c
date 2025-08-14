#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *input_args[] = {"ls", "-l", "/tmp", NULL};

    /* Compare each element until NULL */
			int match = 1;  /* assume match unless proven otherwise */
			int j = 0;
			while (args[j] != NULL && input_args[j] != NULL)
			{
				if (strcmp(args[j], input_args[j]) != 0)
				{
					match = 0;
				}
				j++;
			}
    /* If one list ended before the other, they don't match */
			if ((args[j] != NULL || input_args[j] != NULL))
			match = 0;

			if (!match)
			{
 				fprintf(stderr, "Arguments do not match expected command.\n");
				exit(EXIT_FAILURE);
			}

    /* If match, run execve */
			if (execve("/bin/ls", args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return 0;
}
