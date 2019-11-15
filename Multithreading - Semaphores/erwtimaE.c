#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */



typedef sem_t Semaphore; 



/* semaphores are usually declared global variables */
/* synch semaphore 	  			    */
Semaphore *synch1;
Semaphore *synch2;

int main ()
{
    int   i;                        /*      loop variables  */
    pid_t pid[5];                   /*      fork pid        */
    int child_status;
	
    system("clear"); 





    synch1 = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 0); 
    synch2 = sem_open ("Sem2", O_CREAT | O_EXCL, 0644, 0);     	



    for (i=0; i<5; i++)
    {
        pid[i] = fork ();

        if (pid[i] == 0) 
	{
           break;
        }
    }


    /* 3rd child */
    if (pid[0] != 0 && pid[1] != 0 && pid[2] == 0)
   {

                 
       printf ("\n Child 3 \n");
       sem_post (synch2);
   }
   /* 4th child */
   else if (pid[0] != 0 && pid[1] != 0 && pid[2] != 0 && pid[3] == 0)
   {   

       sem_wait (synch1);
       sem_wait (synch2);       
       usleep(500);
       system ("echo Child 4 is using cat to preview the following sample.txt content: '\n'  ; cat sample.txt");
      
       sem_post (synch1);           
       
   }
   /* 5th child */
   else if (pid[0] != 0 && pid[1] != 0 && pid[2] != 0 && pid[3] != 0 && pid[4] == 0)
   {

       sem_wait (synch1);
       sem_wait (synch2);
       system ("echo Child 5 informs you that our current working directory is:  ; pwd");
       
   }
   /* 2nd child */
   else if (pid[0] != 0 && pid[1] == 0)
   {

       
       system ("echo '\n' Child 2 using sed to replace text in sample.txt ; sed -i 's/.*/Finally, these projects took forever!/g' sample.txt");
       sem_post (synch2);
   }

   /* 1st child */
   else if (pid[0] == 0)
   {
	
       printf ("Child 1 lists all files with details in current directory \n");
       system("ls -l");
       sem_post (synch1);
       
   }

   else
   {
	for (i = 0; i < 5; i++)
	{
	    pid_t wpid = waitpid(pid[i], &child_status, 0);

	    if (WIFEXITED(child_status))
            {
               printf("\n Child: %d terminated with exit status %d\n\n", wpid, WEXITSTATUS(child_status));
            }
            else
            {
               printf("\n Child: %d terminate abnormally\n", wpid);
            }
        }


        printf("\n Unlinking semaphores in parent \n Bye\n");

        /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        sem_unlink ("Sem1");   
        sem_close(synch1);  
        sem_unlink ("Sem2");   
        sem_close(synch2);    
    }


    exit (0);
}


