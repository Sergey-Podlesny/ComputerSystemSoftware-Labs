#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header.h"
#include <time.h>


int main() {

    pid_t childId;
    time_t t;
    int status;

    childId = fork();
    if (childId == -1) {
        perror("fork() error");
    }
    else if(childId == 0) {
        menu();
    }
    else do{
            if ((childId = waitpid(childId, &status, WNOHANG)) == -1)
                perror("wait() error");
            else if (childId == 0) {
                time(&t);
                printf("%s", ctime(&t));
                sleep(2);
            }
            else {
                if (WIFEXITED(status))
                    printf("child exited with status of %d\n", WEXITSTATUS(status));
                else puts("child did not exit successfully");
            }

    } while(childId == 0);

    return 0;
}