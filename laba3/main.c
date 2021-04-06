#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "header.h"





int main() {
    time_t t;
    pid_t pid;
    pid = fork();
    exitNum = 1;
    intNum = 0;
    switch (pid) {
        case -1:
            perror("error");
            exit(-1);
        case 0:
            printf("start child\n");
            childProc();
            printf("end child\n");
            exit(1);
        default:
            printf("start parent\n");
            parentProc(pid);
            printf("end parent\n");
    }
    return 0;
}