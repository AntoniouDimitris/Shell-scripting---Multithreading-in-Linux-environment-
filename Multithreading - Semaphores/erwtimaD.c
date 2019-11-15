#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int nothing(int x)
{
	
	x = x + 1;
	
	return x;

}

int main ()
{
	int status;
	int x = 0;	
	int i = 1;
	float mesos;
	int pid;
	int var;
	time_t start, end;
	int child_pids[100];

	start = time(NULL);
	printf ("Arxiki timi defteroleptwn: %ld\n", start);
	
	

	while ( i < 2500 )
	{
		pid = fork();

		if ( pid == 0 )
		{
			child_pids[i] = getpid();
			//printf ("eimai o %i \n", getppid());
			break;
		}

		x = nothing(x);

		printf("%i\n", x);
		i++;

	}

	if ( pid != 0 && pid != -1 ) 
	{
		for (i=1; i<2500; i++)
		{
			waitpid(-1, &status, 0);
		
		}
		
		end = time(NULL);
		printf("Teliki timi defteroleptwn %i\n", end);
		mesos = end-start;
		printf("O sinolikos xronos ektelesis twn 2500 diergasiwn einai: %2f\n", mesos);
		mesos = mesos / 2500;
		printf("O mesos xronos ektelesis twn 2500 diergasiwn einai: %4f\n", mesos);
	}



	
	return 0;


}
	
