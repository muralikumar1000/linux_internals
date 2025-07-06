#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t alarm_triggered = 0;
//signal handler
void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
    alarm_triggered = 1;
	
}
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if(argc < 2 || argc > 3) {
        printf("Usage: %s <time> [<date>]\n", argv[0]);
        return 1;
    }

    const char *date_str = argv[1];// The time string
    //const char *date_str = "12:00";
    struct tm tm = {0};
    time_t time_now;

    // Parse the time string
    char *result = strptime(date_str, "%H:%M", &tm);
        if (result == NULL) {
            printf("Parsing failed!\n");
            return 1;
        } 

    // Check if the date string is provided
    // If not, use the current date
    if(argv[2] == NULL) {
        time_now = time(NULL);
       struct tm *tm_ptr = localtime(&time_now);
        if (tm_ptr == NULL) {
            perror("localtime");
            return 1;
        }
        tm.tm_year = tm_ptr->tm_year;
        tm.tm_mon = tm_ptr->tm_mon;
        tm.tm_mday = tm_ptr->tm_mday;
        
    }
    // If a date string is provided, parse it
    else if(argv[2] != NULL) {
        date_str = argv[2];
        result = strptime(date_str, "%d/%m/%Y", &tm);
        if (result == NULL) {
            printf("Parsing failed!\n");
        }
    }

    /*printf("Parsed time: %04d-%02d-%02d %02d:%02d:%02d\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    */

    time_t time_to_alarm = mktime(&tm);
    if (time_to_alarm == -1) {
        perror("mktime");
        return 1;
    }
    time_now = time(NULL);
    if (time_now == -1) {
        perror("time");
        return 1;
    }
    double seconds_until_alarm = difftime(time_to_alarm, time_now);
    if (seconds_until_alarm < 0) {
        printf("The specified time is in the past.\n");
        return 1;
    }
    /*else{
        printf("Alarm set for %s, %ld\n", date_str, (long)seconds_until_alarm);
    }*/

   struct sigaction newact;
   memset(&newact, 0, sizeof(newact)); //Clear memory
    newact.sa_flags = SA_SIGINFO;
    newact.sa_sigaction = mysig_handler; //Assign your signal handler
    sigaction(SIGALRM, &newact, NULL);
    alarm(seconds_until_alarm);

    while(1){
        if(alarm_triggered == 1) {
            alarm_triggered = 0;
            printf("Wake-up...Alarm!!\n");
            printf("1.Snooze\t2.Exit\n");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Snooze activated for 1 minute.\n");
                alarm(60); // Sleep for 5 minutes
                //printf("Snooze time is over. Alarm ringing again!\n");
            } else if (choice == 2) {
                printf("Exiting the alarm.\n");
                //signal(SIGALRM,SIG_DFL);
                exit(0);
            }
        }
        pause();
    }



    return 0;
}
