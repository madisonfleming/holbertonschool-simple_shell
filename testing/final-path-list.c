#include <stdio.h>
#include <stdlib.h>
#include <string.h>

path_node_t *new_node(const char *directory)
{ 	path_node_t *new_node = malloc(sizeof(path_node_t));
	if (new_node == NULL)
		return (0);

	new_node->directory = strdup(directory);
	if (new_node->directory == NULL)
	{
		free(new_node);
		return (0);
	}
	new_node->next = NULL;
	return (new_node);
}

path_node_t *linked_list() 
{
	char *path_env = getenv(“PATH”);
	if (path_env == NULL)
	{
		printf(“Error”);
		return NULL;
	}
	char *path_copy = strdup(path_env);
	if (path_copy == NULL)
		printf (“ERROR”)
		return 0;

	path_node_t *head = NULL;
	path_node_t *current = NULL;
	char *token;

	token = strtok(path_copy, “:”);
	while (token != NULL)
	{ 		path_node_t *new_node = create_node(token);
		if (head == NULL);
		{
			head = new_node;
			current = new_node;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
		token = strtok(NULL, “:”);
	}
	free(path_copy);
	return (head);
}

void print_linked_list(path_node_t *head)
{
	path_node_t *current = head;
	while (current != NULL)
	{
		printf(“%s\n”, current->directory);
		current = current->next;
	}
}
 void free_path_ist(path_node_t *head) 
{
        path_node_t *current = head;
        path_node_t *next_node;
        while (current != NULL) 
	      {
            next_node = current->next;
            free(current->directory);
            free(current);
            current = next_node;
        }
    }
