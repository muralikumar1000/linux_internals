/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Date           : Tue 01 Mar 2016 16:18:10 IST
 *   File           : t015.c
 *   Title          : IPC mechanism - Usage of Shared memory - Writer
 *   Description    : IPC mechanisms provide various ways and means to share 
 *                    information between multiple processes. Shared memory 
 *                    offers best performance in terms of speed as it avoids 
 *                    copying data un-necessarily. Here is an example of shared 
 *                    memory (writer) program that writes the data. 
 *
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* Define the shared memory size */
#define SMSIZE 100

int main()
{
		int shmid,num;
		int *shm;
		key_t key;

		/* Key can be hardcoded, but use the same in reader & writer */
		key = 'B';


		/* Create a shared memory */
		shmid = shmget(key,SMSIZE,IPC_CREAT | 0664);

		if (shmid < 0)
		{
				perror("shmget");
				exit(1);
		}
		else
		{
				printf("Created shm with ID = %d\n", shmid);
				shm = shmat(shmid,NULL,0); //Attach to shared memory. Returns the address of shm
				printf("Enter the number\n");
				scanf("%d",&num);

				/* This is the reason why shared memory is the fastest form of IPC. You are manipulating
				   the shared memory as if it is a local pointer. This avoids un-necessary copy with Kernel */
				*shm = num;

				//Detach from shm
				shmdt(shm);
		}
}
