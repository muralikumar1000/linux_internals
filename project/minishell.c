#include "main.h"

 char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

int exit_status;

int IsSpecialVariables(char *input){

    char command[strlen(input) + 1];
    get_command(input, command);
    
    // Handle special variables
    if(!strcmp(command, "echo")){

        strcpy(command, input + strlen(command) + 1); // Skip the command and space
        if(!strcmp(command, "$?")) {//exit status of the previous command
            printf("%d\n", exit_status);
        }
        else if(!strcmp(command, "$$")) {// Print the process ID
            printf("%d\n", getpid());
        }
        else if(!strcmp(command, "$SHELL")) {//path of mini shell
            char buffer[128];
            FILE *fp = popen("pwd", "r");  // Open a pipe to execute "pwd"

            if (fp == NULL) {
                perror("popen failed");
                return 1;
            }

            // Read the output of pwd (typically one line)
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                // Remove the newline character if present
                buffer[strcspn(buffer, "\n")] = '\0';
                printf("%s/", buffer);
            }

            pclose(fp);  // Close the pipe
        }
        else{
            printf("%s\n", command);
        }
        return SUCCESS; 
        
    }
    return FAILURE;

}
void get_command(char *input, char *command) {
    // Extract the command from the input string
    for(; *input && *input != ' ' && *input != '\0'; input++) {
        *command++ = *input;
    }
    *command = '\0'; // Null-terminate the command string 

}

int check_command_type(char *input){
    char cmd[strlen(input) + 1];
    get_command(input, cmd);
    char **builtin = builtins;
    for(;*builtin != NULL ; builtin++){
        if(!strcmp(cmd, *builtin)){
            return BUILTIN;
        }
    }
    return EXTERNAL; // If not a builtin, treat as external command

}

int main(){
   

    char PS1[50] = "minishell", input[100];

    while(1){
        printf("%s$ ", PS1);
        fgets(input, sizeof(input), stdin);
        //input[strcspn(input, "\n")] = 0; // Remove trailing newline
        if(input[0] == '\n') {
            continue; // Skip empty input
        }
        input[strlen(input) - 1] = '\0'; // Remove trailing newline

        if(!strncmp(input, "PS1=", 4) ){
            strcpy(PS1, input+4);
        }
        else if(IsSpecialVariables(input) == SUCCESS) {
            continue; // Skip further processing for special variables
        }
        else if(check_command_type(input) == EXTERNAL) {
            printf("Executing external command: %s\n", input);
            extract_external_commands(input);
        }
        
    }
} 
