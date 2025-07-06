#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <filename> -w-l-c\n", argv[0]);
        return 1;
    }
    int opt, w_flag = 0, l_flag = 0, c_flag = 0;
    extern int optind;
    while((opt = getopt(argc, argv, "wlc")) != -1) {
        switch(opt) {
            case 'w':
                w_flag = 1;
                break;
            case 'l':
                l_flag = 1;
                break;
            case 'c':
                c_flag = 1;
                break;
        }
    }
    FILE *fp = fopen(argv[optind], "r");
    if(fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    int word_count = 0, line_count = 0, char_count = 0;
    char c, prev ;
    while((c = fgetc(fp)) != EOF) {
        if(c_flag){
            char_count++;
        }
        
        if(w_flag && (isspace(c) && prev != ' ' && prev != '\t')) {
            word_count++;
        }
        if(l_flag && c == '\n') {
            line_count++;
            word_count++;
        }
        prev = c;
    }
    printf("Word count: %d\n", word_count);
    printf("Line count: %d\n", line_count);
    printf("Character count: %d\n", char_count);
    fclose(fp);
    return 0;
}