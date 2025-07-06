/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:18:10 IST
 *   File           : t015.c
 *   Title          : IPC mechanism - Usage of Shared memory - Reader 
 *   Description    : IPC mechanisms provide various ways and means to share 
 *                    information between multiple processes. Shared memory 
 *                    offers best performance in terms of speed as it avoids 
 *                    copying data un-necessarily. Here is an example of shared 
 *                    memory (reader) program that reads data. 
 *
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SMSIZE 100

int main()
{
    int shmid;
    key_t key;
    int *shm;

    /* Use the same key as in writer */
 	key = 'B';

    /* Get the shared memory, creation is already done */
	shmid = shmget(key,SMSIZE, 0664);
	printf("Got shm with ID = %d\n", shmid);

    if (shmid < 0)
    {
    	perror("shmget");
    	exit(1);
    }

	/* Attach to shared memory */
    shm = shmat(shmid,NULL,0);
    if (shm < 0)
    {
    	perror("shmat");
    	exit(0);
    }
    else
    {
		/* Read the value from shared memory and print */
		printf("Value from shared memory: %d\n",*shm);
	}
	
	/*
	 * TODO: 1. Detach & remove the shared memory. Confirm deletion by executing ipcs
	 *       2. Extend this program for assignment in order to exhange string
	 */


    // Detach from shm
    shmdt(shm);

    //Remove shared memory
    //shmctl(shmid, IPC_RMID, 0);
 	  struct shmid_ds shm_ds; 
      shmctl(shmid, IPC_STAT, &shm_ds);
	  printf("Shared memory info :\n");
	  printf("Id of Shared memory is %d\n",shmid);
	  printf("Creator process pid is %d\n",shm_ds.shm_cpid);


		







 

}
