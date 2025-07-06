#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
 
#define SUCCESS 0
#define FAILURE 1
#define BUILTIN		2
#define EXTERNAL	3
#define NO_COMMAND  4
#define MAX_ARGS 10

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void scan_input(char *prompt, char *input_string);
void get_command(char *input, char *command);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *input);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char *input);

#endif