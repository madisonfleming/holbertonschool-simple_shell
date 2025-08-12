#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t current_pid = getpid();
	pid_t parent_pid = getppid();

	printf("%u\n", current_pid);
	printf("%u\n", parent_pid);
return (0);
}
