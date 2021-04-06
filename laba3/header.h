//
// Created by s3rp0d on 06/04/2021.
//

#ifndef LABA3_HEADER_H
#define LABA3_HEADER_H


int intNum;
int exitNum;

void parentProc(pid_t);

void childProc();

void signalP2CHandler();

void signalC2PHandler();

int kbhit();

#endif //LABA3_HEADER_H
