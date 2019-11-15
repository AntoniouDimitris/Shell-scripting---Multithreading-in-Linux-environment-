#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int pid;


	for (i=0; i<5; i++)
	{
		pid = fork();

		if (pid > 0)
		{
			printf(" Father = %i, Id = %i, Child = %i\n", getppid(), getpid(), pid);
			wait (NULL);
			break;
		}
	}
	
	return (0);
}
