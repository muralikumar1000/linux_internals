/*------------------------------------------------------------------------------ 
 *
 *   Author         : Emertxe (http://www.emertxe.com) 
 *   Title          : Semaphore usage - Multi-process condition  
 *   Description    : Race condition is common in multi-processing situation
 *                    as shared data condition will come there as well.Problem 
 *                    is solved by process semaphores, demonstrated here. 
 *
 *----------------------------------------------------------------------------*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{
	int semid, pid;
	struct sembuf sop;
	
	//Creating the semaphore
	semid = semget(0x20, 1, IPC_CREAT | 0666);
	//Initializing the semaphore
	semctl(semid, 0, SETVAL, 1);
	//
	pid = fork();
	if(pid == 0)
	{
		printf("child before semop\n");
		//Wait operation
		sop. sem_num = 0; 
		sop.sem_op = -1;
		sop.sem_flg = 0;
		semop(semid, &sop, 1);

		printf("Child in critical section\n");
		sleep(10);
		printf("Child coming out of critical section\n");
		//Post operation
		sop.sem_num = 0; 
		sop.sem_op = 1; 
		sop.sem_flg = 0;
		semop(semid, &sop, 1);
	}
	else
	{
		printf("parent before semop\n");
		//Wait operation
		sop. sem_num = 0; 
		sop.sem_op = -1;
		sop.sem_flg = 0;
		semop(semid, &sop, 1);
		printf("Parent in critical section\n");
		sleep(10);
		printf("Parent coming out of critical section\n");
		//Post operation
		sop.sem_num = 0; 
		sop.sem_op = 1; 
		sop.sem_flg = 0;
		semop(semid, &sop, 1);
	}
	return 0;
}
