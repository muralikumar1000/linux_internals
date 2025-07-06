#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void mysig_handler(int num)
{
    printf("Signal number %d\n", num);
    signal(SIGSEGV, SIG_DFL); // Reset to default handler
}

int main(){
    signal(SIGSEGV, mysig_handler);

    int *p = NULL;
    *p = 10; // This will cause a segmentation fault

}
