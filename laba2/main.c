#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]) {
    char *name = getOptions("name", argv, argc);
    char *user = getOptions("user", argv, argc);
    char *group = getOptions("group", argv, argc);
    char *type = getOptions("type", argv, argc);
    char *perm = getOptions("perm", argv, argc);
    char *path = (char *) malloc(50);
    strcpy(path, "/home/s3rp0d/CLionProjects/Apk/Test");
    DIR *dir = opendir(path);
    char template[50] = "laba2XXXXXX";
    int fd = mkstemp(template);

    FILE *file = (FILE *) malloc(sizeof(FILE));
    file = fopen(template, "r+");
    if (fd == -1 || file == NULL || !dir) {
        perror("file system error");
        closeFiles(fd, dir, template);
        return 1;
    }
    scanFileTree(dir, path, name, user, group, type, perm, file);
    readDataFromFile(file, fd);
    closeFiles(fd, dir, template);
    return 0;
}
