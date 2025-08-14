#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sshell.h"

path_node_t *new_node(const char *directory)
{
	path_node_t *node = malloc(sizeof(path_node_t));
	if (node == NULL)
		return (NULL);

	node->directory = strdup(directory);
	if (node->directory == NULL)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

path_node_t *linked_list(void)
{
	char *path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("Error-getenv");
		return NULL;
	}
	char *path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		perror("ERROR-strdup");
		return NULL;
	}
	path_node_t *head = NULL;
	path_node_t *current = NULL;
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		path_node_t *node = new_node(token);
		if (node == NULL)
		{
			perror("Error-newnode");
			free(path_copy);
			return NULL;
		}
		if (head == NULL)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = node;
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (head);
}
int main(void)
{
	path_node_t *list = linked_list();
	path_node_t *current = list;

	while (current != NULL)
	{
		printf("%s\n", current->directory);
		current = current->next;
	}
	return 0;
}
