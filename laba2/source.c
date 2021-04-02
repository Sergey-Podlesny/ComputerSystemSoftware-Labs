#include "header.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

void scanFileTree(DIR *dir, char *path, char *name, char *user, char *group, char *type, char *perm,
                  FILE *file) {
    struct dirent *entry;
    char *currentPath = (char *) malloc(200);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == 4) {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
                continue;
            }
            if ((name == NULL || !strcmp(entry->d_name, name)) && (type == NULL || entry->d_type == 4) &&
                (type == NULL || !strcmp(type, "folder")))
                writeDataToFile(user, group, path, entry, file);
            currentPath = getCurrentPath(entry, path);
            DIR *newDir = opendir(currentPath);
            if (!newDir) {
                continue;
            }
            scanFileTree(newDir, currentPath, name, user, group, type, perm, file);
            closedir(newDir);
        } else {
            if ((name == NULL || !strcmp(entry->d_name, name)) && (type == NULL || entry->d_type == 8) &&
                (type == NULL || !strcmp(type, "file")) &&
                (perm == NULL || checkPermission(getCurrentPath(entry, path), atoi(perm))))
                writeDataToFile(user, group, path, entry, file);
        }
    }
    free(currentPath);
}

void writeDataToFile(char *user, char *group, char *path, struct dirent *entry, FILE *file) {
    struct stat *info = (struct stat *) malloc(sizeof(struct stat));
    stat(path, info);

    struct passwd *pw = getpwuid(info->st_uid);
    struct group *gr = getgrgid(info->st_gid);
    if ((user == NULL || !strcmp(pw->pw_name, user)) && (group == NULL || !strcmp(gr->gr_name, group))) {
        fprintf(file, "%s/%s - Owner - %s    Group - %s  Type-%d\n", path, entry->d_name, pw->pw_name, gr->gr_name,
                entry->d_type);
        fflush(file);
    }
}

int checkPermission(char *path, int perm) {
    int currentPerm = 0;
    int R = (access(path, R_OK) == 0) ? 1 : 0;
    int W = (access(path, W_OK) == 0) ? 1 : 0;
    int X = (access(path, X_OK) == 0) ? 1 : 0;
    if (!access(path, F_OK)) {
        if (!R && !W && !X) {
            currentPerm = 0;
        } else if (!R && !W && X) {
            currentPerm = 1;
        } else if (!R && W && !X) {
            currentPerm = 2;
        } else if (!R && W && X) {
            currentPerm = 3;
        } else if (R && !W && !X) {
            currentPerm = 4;
        } else if (R && !W && X) {
            currentPerm = 5;
        } else if (R && W && !X) {
            currentPerm = 6;
        } else if (R && W && X) {
            currentPerm = 7;
        }
    }
    return currentPerm == perm;
}


char *getOptions(const char *paramName, char **argv, int argc) {
    char *param = NULL;
    for (int i = 1; i < argc; i += 2) {
        if (!strcmp(argv[i], paramName)) {
            char *param = (char *) malloc(20);
            strcpy(param, argv[i + 1]);
            return param;
        }
    }
    return param;
}

void readDataFromFile(FILE *file, int fd) {
    char stringFromFile[100];
    fseek(file, 0, 0);
    fgets(stringFromFile, 100, file);
    while (!feof(file)) {
        printf("%s\n", stringFromFile);
        fgets(stringFromFile, 100, file);
    }
}

char *getCurrentPath(struct dirent *entry, char *path) {
    char *currentPath = (char *) malloc(200);
    int length = strlen(entry->d_name);
    strcpy(currentPath, path);
    size_t symbolLength = 1;
    strncat(currentPath, "/", symbolLength);
    strncat(currentPath, entry->d_name, length);
    return currentPath;

}

void closeFiles(int fd, DIR *dir, char *template) {
    closedir(dir);
    close(fd);
    unlink(template);
}
