#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void print_process_status(pid_t pid) {
    char path[64], buffer[1024];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Could not open status file");
        return;
    }

    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (bytes <= 0) return;
    buffer[bytes] = '\0';

    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        if (strncmp(line, "Name:", 5) == 0 || strncmp(line, "State:", 6) == 0)
            printf("%s\n", line);
        line = strtok(NULL, "\n");
    }
}

int main() {
    pid_t zombie_pid, orphan_pid;

    zombie_pid = fork();

    if (zombie_pid < 0) {
        perror("fork for zombie failed");
        exit(EXIT_FAILURE);
    }

    if (zombie_pid == 0) {
        // Zombie child
        printf("A child created with pid %d\n", getpid());
        
        sleep(2); // Short delay to let parent print info
        exit(0);
    } else {
        sleep(1); // Give time for child to become zombie
        print_process_status(zombie_pid);
        sleep(2); // Give time for zombie to exit
        printf("Checking child process status:\n");
        print_process_status(zombie_pid);  // Should be sleeping/zombie soon

        sleep(3); // Let the zombie persist

        orphan_pid = fork();

        if (orphan_pid < 0) {
            perror("fork for orphan failed");
            exit(EXIT_FAILURE);
        }

        if (orphan_pid == 0) {
            sleep(5); // Parent will exit before this finishes
            printf("Orphan child. My PID: %d, My Parent PID: %d\n", getpid(), getppid());
            exit(0);
        } else {
            printf("Parent exiting now. Zombie still exists. Orphan will be adopted.\n");

            // Don't wait for zombie, it will remain
            // Also don't wait for orphan, it'll be adopted
            exit(0);
        }
    }

    return 0;
}
