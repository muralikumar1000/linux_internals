/*Documentation
Name           : U.Nagavenu
Date           : 08/05/2023   
Description    : Implement communication between two related processes using one pipe
Sample Input   : ./a.out ls -l '|' wc
Sample Output  :       3      20     122
Documentation*/


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{

    // Check if there are sufficient arguments passed to the program
    if (argc < 4) 
    {
	printf("Error: Insufficient arguments passed. Usage: ./pipe <command1> '|' <command2>\n");
	return 1;
    }

    int pos = 0;

    // Find the position of the '|' character in the arguments
    while (argv[pos] != NULL) 
    {
	if (strcmp(argv[pos], "|") == 0) 
	{

	    argv[pos] = NULL;   // Replace '|' with NULL to terminate the first command
	    pos = pos + 1;
	    break;
	} 
	else 
	{
	    pos++;
	}
    }

    // If '|' is not found in the arguments, print an error message and exit
    if (argv[pos] == NULL) 
    {
	printf("'|' not found. Usage: ./pipe <command1> '|' <command2>\n");
	return 1;
    }

    int fd[2];
    pipe(fd);   // Create a pipe

    int pid = fork();   // Fork the first child process

    if (pid == 0) 
    {   // In the first child process

	close(fd[0]);   // Close the read end of the pipe
	dup2(fd[1], 1);   // Duplicate the write end of the pipe to standard output (1)
	execvp(argv[1], argv + 1);   // Execute the first command with its arguments

    } 
    else 
    {   // In the parent process

	int pid2 = fork();   // Fork the second child process

	if (pid2 == 0) 
	{   // In the second child process

	    close(fd[1]);   // Close the write end of the pipe
	    dup2(fd[0], 0);   // Duplicate the read end of the pipe to standard input (0)
	    execvp(argv[pos], argv + pos);   // Execute the second command with its arguments

	} 
	else
	{   // In the parent process

	    close(fd[0]);   // Close both ends of the pipe
	    close(fd[1]);
	    wait(NULL);   // Wait for the first child process to finish
	    wait(NULL);   // Wait for the second child process to finish

	}
    }

    return 0;
}




