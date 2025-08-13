#include <stdio.h>
#include <unistd.h> /*required for environ */
/**
 * main - prints the environment
 * @environ is a pointer to an array of pointers to character strings
 * Return: Always 0.
 */

extern char **environ;

int main(int ac, char **av, char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
