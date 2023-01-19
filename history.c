#include "headers.h"
#include "history.h"
#include "stdlib.h"

void history(int argc, char *argv[])
{
    int num;
    if (argc > 1)
    {
        perror("Too many arguments\n");
        return;
    }
    else if (argc == 1)
    {
        // num = atoi(argv[1]);
        // if (num < 0)
        // {
        perror("Invalid command\n");
        // }
    }
    // else if (argc == 0)
    // {

    // }
    // if (num > 10)
    // {
    //     num = 10;
    // }
   
    if (total < 10)
    {
        for (int i = 0; i < total; i++)
        {
            printf("%s", array[i]);
        }
    }
    else{
        for(int i=total-10;i<total;i++)
        {
            printf("%s",array[i]);
        }
    }
}
void add_command(char *argv)
{
    // printf("prev = %s\n",prev_cmd);
    // printf("current = %s\n",argv);
    if(strcmp(prev_cmd,argv) == 0)
    {
        // printf("dja\n");
        return;
    }
    if (total < 20)
    {
        strcpy(array[total++], argv);
    }
    else
    {
        for (int i = 1; i < 20; i++)
        {
            strcpy(array[i - 1], array[i]);
        }
        strcpy(array[19], argv);
    }
}
void write_hist(FILE *fptr)
{
    for (int i = 0; i < total; i++)
    {
        fprintf(fptr, "%s", array[i]);
    }
}
void read_hist(FILE *fptr)
{
    fptr = fopen("history.txt", "r");
    int lines = 0;
    size_t buf = 0;
    char *buffer;
    while (getline(&buffer, &buf, fptr) != -1)
    {
        buffer[strlen(buffer) - 1] = '\n';
        strcpy(array[lines], buffer);
        lines++;
    }
    total = lines;
}