#ifndef LS_H
#define LS_H

void ls(int,char**);
void sortStrings(char arr[][1000], int n);
int is_regular_file(char *path);
int isDirectory(char *path);
int isExec(char* path);
void print_ls(int,char*,int);
void permission_ls(char*);
#endif