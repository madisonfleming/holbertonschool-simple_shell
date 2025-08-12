#include <stdio.h>
#include <limits.h>
#include <sys/types.h>

int main()
{
	if (sizeof(pid_t) == sizeof(short))
	{
		printf("%d\n", SHRT_MAX);
	}
	if (sizeof(pid_t) == sizeof(int))
	{
		printf("%d\n", INT_MAX);
        }
	if (sizeof(pid_t) == sizeof(long))
	{
		printf("%ld\n", LONG_MAX);
	}
	return (0);
}
