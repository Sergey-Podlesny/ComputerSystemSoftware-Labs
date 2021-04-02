#include <stdio.h>
#include <dirent.h>

#ifndef LABA2_HEADER_H
#define LABA2_HEADER_H

char *getParam(const char *paramName, char *argv[], int argc);

char *createNewCurrentPath(struct dirent *entry, char *path);

int checkPerm(char path[100], int perm);

void printInfoFromFile(FILE *file, int fd);

void closeAll(int fd, DIR *dir, char *template);

void
goThroughFileTree(DIR *dir, char path[200], char name[20], char user[20], char group[20], char type[20], char perm[20],
                  FILE *file);

void printInfoToFile(char user[20], char group[20], char path[200], struct dirent *entry, FILE *file);

#endif //LABA2_HEADER_H
