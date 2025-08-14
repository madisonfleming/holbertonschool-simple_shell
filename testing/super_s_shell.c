#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
    char command[1024];
    char *argv[2];
    int stat;

    while (1)
    {
        printf("$ "); /* Prompt */

        if (!fgets(command, sizeof(command), stdin))
            return 0; /* Ctrl+D */

        command[strcspn(command, "\n")] = '\0'; /* Remove newline */

        argv[0] = command;
        argv[1] = NULL;

        if (fork() == 0)
            execve(command, argv, NULL), perror("execve"), _exit(1);

        wait(&stat); /* Wait for child */
    }
}
