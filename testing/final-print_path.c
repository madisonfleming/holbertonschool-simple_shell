#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
    char **env_pointer = environ;
    size_t name_len = strlen(name);

    while (*env_pointer != NULL)
    {
        if (strncmp(*env_pointer, name, name_len) == 0 && (*env_pointer)[name_len] == '=')
        {
            return *env_pointer + name_len + 1;
        }
        env_pointer++;
    }
    return NULL;
}

void print_directory(void)
{
    char *path_value = _getenv("PATH");
    if (path_value == NULL)
    {
        printf("PATH not found\n");
        return;
    }

    char *path_copy = strdup(path_value);
    if (path_copy == NULL)
    {
        printf("strdup");
        return;
    }
    char *token = strtok(path_copy, ":");
    while (token != NULL)
    {

        printf("%s\n", token);
        token = strtok(NULL, ":");
    }
    free(path_copy);
}

int main(void)
{
    print_directory();
    return 0;
}
