/*
<<doc
Name: Murali venkata vijay kumar
Date:
Description:
Sample i/p:
Sample o/p:
doc
*/
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<errno.h>
#include <sys/wait.h>

int is_prime(int);
int generate_prime(int limit, int source_fd);
int fibonnaci(int limit, int source_fd);

int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Insufficient arguments\nUsage:- %s filename",argv[0]);
		return 1;
	}

	int src_fd = open(argv[1], O_WRONLY);
	if(src_fd == -1){
		perror("open");
		return 2;
	}

	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		return 3;
	}

	struct flock fl;
	memset(&fl, 0, sizeof(fl));
////////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////////////////////
	/* this if will run inside parent process */
	if(pid > 0){
		fl.l_type = F_WRLCK;//lock type, write is set
		fcntl(src_fd, F_SETLKW, &fl);//lock type is applied to file

		/* up to 150,prime numbers are generated and written to source_file from this function */
		generate_prime(150,src_fd);



		fl.l_type = F_UNLCK;//lock type, unlock is set
		fcntl(src_fd, F_SETLKW, &fl);//lock type is applied to file

		/* parent process will wait until child is finished*/
		wait(0);
		

	}
	/* this if will run inside child process */
	else if(pid == 0){
		fl.l_type = F_WRLCK;
		fcntl(src_fd, F_SETLKW, &fl);//file get locked until operation is finished
		
		/* up to 100 fibonacci series is generated*/
		fibonnaci(100,src_fd);

		fl.l_type = F_UNLCK;
		fcntl(src_fd, F_SETLKW, &fl);//file is unlocked after operation finished
	}

}
////////////////////////////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////////////////////
int is_prime(int num){
        int sqrt = 0, s = 0, count = 0;
        while (sqrt <= num){ //for finding squareroot
        s++;           //will increment s until it gives squareroot equal
        sqrt = s * s;  //it gives square root value
        }
    sqrt = s - 1; //extra  one value is generated while finding squareroot is negated

        for (int i = 2; i <= sqrt; i++){ //as prime multiples starts from 2, hence loop starts from 2 to square root of num
                if( num % i == 0){ //if there is a multiple of 2,3,4...num
                        count++; //count gets incremented
                        break; //loop breaks out thereafter
                }
        }

        if ( count == 0){ //if count is 0, then its a prime
                return 1;
        }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int generate_prime(int limit, int src_fd){

	ssize_t wr_ret;
	int i;

	wr_ret = write(src_fd, "prime numbers upto 150 are \n",28);
	if(wr_ret == -1){
		perror("write");
		return 4; 
	}

        for (i = 2; i <= limit; i++){//as primes start from 2, loop is from 2 to limit
                int ret = is_prime(i); //prime function is called for every i'th number
                if ( ret == 1 ){ //if function returns 1, it's a prime
                        //printf("%d ", i);

						char buff[sizeof(int)];//buffer is set to integer size
						int size = sprintf(buff,"%d ",i); //integer is converted to string with decimal length, size gives string length

						/* write system call to copy evey prime to source file*/
						wr_ret = write(src_fd,buff,size);
						if(wr_ret == -1){
							perror("write");
							return 4; 
						}
                }
        }
		/* for adding new line character to file at the end of operation*/
		if(i == (limit+1)){
			wr_ret = write(src_fd,"\n",1); //new line is directly written at the end of prime operation
			if(wr_ret == -1){
				perror("write");
				return 4; 
			}

		}

        //printf("\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int fibonnaci(int limit, int src_fd){

	/* first line to identify which is what*/
	ssize_t wr_ret = write(src_fd,"Fibonnaci series upto 100 are \n",31);//write pushes string to source file
	if(wr_ret == -1){
		perror("write");
		return 5;
	}

    int first = 0 , next = 0;
    int second = 1;
            while ( next <= limit){ //runs until fibonacci sequence reaches user input number
                    //printf("%d ",next); //prints fibonacci numbers in sequence

					char buff[sizeof(int)];
					int size = sprintf(buff,"%d ",next);//integer in $next is pushed as string to buff


					wr_ret = write(src_fd, buff,size);//write pushes string in buff to source file
					if(wr_ret == -1){
						perror ("write");
						return 5;
					}


                    first = second;
                    second = next;
                    next = first + second;
            }
			wr_ret = write(src_fd,"\n",1);//new line is added at the end of file.
			if(wr_ret == -1){
				perror("write");
				return 5;
			}
            //printf("\n"); //line escape
}
