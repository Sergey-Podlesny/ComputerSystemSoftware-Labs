#include <stdio.h>
#include <dirent.h>

#ifndef LABA2_HEADER_H
#define LABA2_HEADER_H

char *getOptions(const char *paramName, char **argv, int argc);

void scanFileTree(DIR *dir, char *path, char *name, char *user, char *group, char *type, char *perm, FILE *file);

char *getCurrentPath(struct dirent *entry, char *path);

int checkPermission(char *path, int perm);

void readDataFromFile(FILE *file);

void writeDataToFile(char *user, char *group, char *path, struct dirent *entry, FILE *file);

void closeFiles(int fd, DIR *dir, char *template);

#endif //LABA2_HEADER_H
