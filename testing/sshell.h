#ifndef SSHELL_H
#define SSHELL_H

#include <stdlib.h>

typedef struct path_node {
	char *directory;
	struct path_node *next;
} path_node_t;

path_node_t *new_node(const char *directory);
path_node_t *linked_list(void);

#endif
