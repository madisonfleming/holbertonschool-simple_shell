#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int line_no = 1;
char *progname;

char *read_input(void)
{
	char *input_line;
	size_t size;
	ssize_t charsRead;
	int mode;
		
    input_line = NULL;
	size = 0;
	mode = isatty(0);
	
	if (mode == 1)
	{
	    printf("#cisfun$ ");
	    fflush(stdout);
	}
	   
    charsRead = getline(&input_line, &size, stdin);
        
        if (charsRead == -1)
		{
			free(input_line);
			return (NULL);
		}

    	if (charsRead > 0 && input_line[charsRead - 1] == '\n')
		    input_line[charsRead - 1] = '\0'; 
	
return (input_line);
}

char **split_string(char *str)
{
	char **word_array = NULL;
	char *word;
	char *string_copy;
	char *delimiters = " ";
	size_t count = 0, i = 0, j = 0;

	if (str == NULL)
		return (NULL);

	string_copy = strdup(str);
	if (string_copy == NULL)
		return (NULL);

	word = strtok(string_copy, delimiters);
	while (word != NULL)
	{
		count++;
		word = strtok(NULL, delimiters);
	}
	free(string_copy);

	word_array = malloc(sizeof(char *) * (count + 1));
	if (word_array == NULL)
		return (NULL);

	string_copy = strdup(str);
	if (string_copy == NULL)
	{
		free(word_array);
		return (NULL);
	}
	i = 0;
	word = strtok(string_copy, delimiters);
	while (word != NULL)
	{
		word_array[i] = strdup(word);
		if (word_array[i] == NULL)
		{
			while (j < i)
			{
				free(word_array[j]);
				j++;
			}
			free(word_array);
			free(string_copy);
			return (NULL);
		}
		i++;
		word = strtok(NULL, delimiters);
	}
	word_array[i] = NULL;
	free(string_copy);
		return (word_array);
}

void free_args(char **args)
{
	size_t i = 0;

	if (args == NULL)
		return;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void execute_command(char **args)
{
	pid_t child_pid;
	int status;
	extern char **environ;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

int main(int argc, char **argv)
{
	char *command;
	char **args;
	int count, notallspaces;
	
	(void)argc;
	progname = argv[0];

	while (1)
	{
		command = read_input();
		if (command == NULL)
		    exit(0);

		if (strlen(command) == 0)
		{
			free(command);
			line_no++;
			continue;
		}
		
		count = 0, notallspaces = 0;
		
		while (command[count] != '\0')
		{
		    if (command[count] != ' ')
		    {  
		        notallspaces = 1;
		        break;
		    }
		    count++;
		}
		

		if (notallspaces == 0) 
		{
		    free(command);
		    line_no++;
		    continue;
		}
		
		args = split_string(command);
		
		if (args != NULL)
		{
		    execute_command(args);
		    free_args(args);
		}
		    
		free(command);
		line_no++;
	}

	return (0);
}
