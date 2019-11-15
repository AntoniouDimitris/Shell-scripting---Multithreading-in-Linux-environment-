#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	int i;
	pid_t pid;

	for (i = 1; i < 5; i++)
	{
		pid = fork();

		if (pid == 0)
		{
			break;
		}

		printf("\n Eimai i diergasia %i kai afto einai to paidi %i me pid %i \n", getppid(), i, pid);
	}

	return 0;
}


