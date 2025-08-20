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

int count_words(char *str)
{
	int count;
	char *words;
	
	count = 0;
	
	words = strtok(str, " ");
	while (words != NULL)
	{
		count++;
		words = strtok(NULL, " ");
	}

	return (count);
}

void free_args(char **args)
{
        int count;

        if (args == NULL)
                return;

        count = 0;
        while (args[count] != NULL)
        {
                free(args[count]);
                count++;
        }
        free(args);
}

char **split_string(char *str)
{
	char **words_array;
	char *word, *str_copy, *copy_to_count;
	int count, slot;
	
	slot = 0;

	if (str == NULL)
		return (NULL);

	copy_to_count = strdup(str);
	if (copy_to_count == NULL)
		return (NULL);

	count = count_words(copy_to_count);
	free(copy_to_count);
	if (count == 0)
		return (NULL);

	words_array = malloc(sizeof(char *) * (count + 1));
	if (words_array == NULL)
		return (NULL);
	
	str_copy = strdup(str);
	if(str_copy == NULL)
	{
		free(words_array);
		return(NULL);
	}
	
	word = strtok(str_copy, " ");
	while (word != NULL)
	{
		words_array[slot] = strdup(word);
		if (words_array[slot] == NULL)
		{
			free_args(words_array);
			free(str_copy);
			return (NULL);
		}
		slot++;
		word = strtok(NULL, " ");
	}
	words_array[slot] = NULL; /* add NULL to end of array */
	free(str_copy);
	return (words_array);
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
	/* int count, notallspaces; */
	
	(void)argc;
	progname = argv[0];

	while (1)
	{
		command = read_input();
		if (command == NULL)
		    exit(0);
		
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
