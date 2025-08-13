#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* status helper */
int file_found(const char *filepath)
{
    struct stat st;

    if (stat(filepath, &st) == 0)
    {
        /* Check if it’s executable by owner */
        if (st.st_mode & S_IXUSR)
            return 1; // found and executable
    }
    return 0; // not found or not executable
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", av[0]);
        return 1;
    }

    char *path_env = getenv("PATH");
    if (!path_env)
        return 1;

    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");

    while (dir)
    {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, av[1]);

        if (file_found(full_path))
        {
            printf("%s\n", full_path);
            free(path_copy);
            return 0; // stop after first match
        }
        dir = strtok(NULL, ":");
    }

    printf("%s not found in PATH\n", av[1]);
    free(path_copy);
    return 0;
}
