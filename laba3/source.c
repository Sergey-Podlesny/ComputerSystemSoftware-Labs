//
// Created by s3rp0d on 06/04/2021.
//
#include "header.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

void parentProc(pid_t pid) {

    FILE *file;
    if((file = fopen("parentFile.txt", "w+")) == NULL)
    {
        printf("Open file error\n");
        exit(-1);
    }
    time_t t;
    int i = 0;
    while (exitNum) {
        (void)signal(SIGUSR1, signalC2PHandler);
        if (!intNum) {
            fprintf(file, "Hello #%i", i++);
        } else {
            intNum = 0;
            time(&t);
            printf("%s\n", ctime(&t));
            printf("in parentproc\n");
        }
        sleep(1);
        if(kbhit())
        {
            printf("start parent kill\n");
            kill(pid, SIGUSR2);
            printf("end parent kill\n");
            exitNum = 0;
        }
    }
    printf("in end of parent proc\n");
    fclose(file);
}

void childProc() {
    FILE* file;
    if((file = fopen("childFile.txt", "w+")) == NULL)
    {
        printf("Open file error!\n");
        exit(-1);
    }
    while (exitNum)
    {
        (void)signal(SIGUSR2, signalP2CHandler);
        sleep(2);
        kill(getppid(), SIGUSR1);
        fprintf(file, "hello\n");
        printf("in childproc\n");
    }
    fclose(file);
    if(remove("childFile.txt"))
    {
        printf("remove error!\n");
        exit(-1);
    }
}

void signalP2CHandler() {
    exitNum = 0;
}

void signalC2PHandler() {
    intNum = 1;
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

