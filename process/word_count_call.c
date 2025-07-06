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
#include<unistd.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int  my_wc(int fd, int l_flag, int w_flag, int c_flag);

int optind;//variable used by $getopt() function, to store starting index of CLA files

int main(int argc, char *argv[]){

        /* flags for setting, which option is called from CLA */
        int char_flag = 0, word_flag = 0, line_flag = 0;
        char ch;
////////////////////////////////////////////////////////////////////////

        /* from here the GETOPT fun will capture all options from CLA*/
        while((ch = getopt(argc, argv, "lwc")) != -1){

                /* this will set flag based on return value of getopt() */
                switch(ch){
                        case 'c':
                                char_flag = 1;
                                break;
                        case 'w':
                                word_flag = 1;
                                break;
                        case 'l':
                                line_flag = 1;
                                break;
                }
        }
//////////////////////////////////////////////////////////////////////////

        /* if no CLA files are passed, the wordcount function takes input from STDIN*/

        if(argv[optind] == NULL){

                my_wc(0,line_flag,word_flag,char_flag);

        }
        /* if CLA files are passed to wordcount*/
        else{

                /* from starting index, provided by $optind every file is opened*/
                for(int i = optind; argv[i] != NULL; i++){

                        int fd = open(argv[i],O_RDONLY);//opening file in arguments with readonly mode
                        if(fd == -1){
                                perror("open");
                                return 1;
                        }

                        /* FD of file along with option flags are passed*/
                        my_wc(fd,line_flag,word_flag,char_flag);

                        /* to print CLI argument file name, after printig their respective parameters*/
                        printf("%s\n",argv[i]);
                        close(fd);//opened file is closed,FOR loop is itterated until all argument files are finished

                }
        }
}
////////////////////////////////////////////////////////////////////////////////////////////

/* WORD COUNT function to count no.of lines, words, characters in a file or from STDIN*/
int  my_wc(int fd, int l_flag, int w_flag, int c_flag){
        ssize_t rd_ret;

        char chtr;
        char prev;
        int c_count = 0;
        int w_count = 0;
        int l_count = 0;

        /* read system call is iterated to the end of reading file*/
        while((rd_ret = read(fd, &chtr, 1)) > 0){
                if(rd_ret == -1){
                        perror("read");
                        return 2;
                }

                if(c_flag == 1){//for every character count is incremented.
                        c_count++;
                }
                if(w_flag == 1 && chtr == ' ' && prev != ' ' && prev != '\t'){//for every word count is incremented.
                        w_count ++;
                }
                if(l_flag == 1 && chtr == '\n'){//for every new line, line count is incremented and word count also.
                        l_count++;
                        w_count++;
                }
                prev = chtr;//previous character is stored for error correction
        }
        printf("\n%d  %d  %d  ",l_count,w_count,c_count);// all the counts are printed in a single line
}
