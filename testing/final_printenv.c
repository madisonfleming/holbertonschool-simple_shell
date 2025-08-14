#include <stdio.h>
#include <unistd.h> /*required for environ */
/**
 * main - prints the environment
 * @environ is a pointer to an array of pointers to character strings
 * Return: Always 0.
 */

extern char **environ;

int main(int ac, char **av)
{
    unsigned int i;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return (0);
}
