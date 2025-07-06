/*
   1. A pipe is a one way communication channel.
   2. A pipe is created using the system call: pipe()
   3. A pipe is shared only between two processes which are related to each other.
   */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
		//Declare to hold the file descriptors
		int p[2];

		//Create the pipe
		if (pipe(p) == -1)
		{
				perror("PIPE");
				exit(EXIT_FAILURE);
		}

		switch (fork())
		{
				case -1:
						perror("fork()");
						break;
				case 0:
						{
								//Read 
								//close write fd
								printf("Child: \n");
								close(p[1]);
								char buff[6];
								read(p[0],buff,6);
								printf("%s\n",buff);
								close(p[0]);
						}
						break;
				default:
						{
								//Write into pipe
								//close read fd
								close(p[0]);
								printf("Parent: \n");
								write(p[1], "hello",6);
								close(p[1]);
						}

		}
}


/*
   1. p[0], refers to read end
   2. p[1], refers to write end
   */
