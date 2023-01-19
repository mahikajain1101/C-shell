#include "headers.h"
#include "cd.h"
void cd(int num, char *parameter[])
{
    char cwd[MAX];
    getcwd(cwd, MAX);
    char changeto[MAX];
    char dir[MAX];
    if (num < 1)
    {
        strcpy(dir, "~");
    }
    else if (num > 1)
    {
        fprintf(stderr, "cd: Too many arguments\n");
        return;
    }
    else
    {
        strcpy(dir, parameter[1]);
    }
    if (strcmp(dir, "-") == 0)
    {
        strcpy(changeto, prev_dir);
        printf("%s\n", prev_dir);
    }
    else if (strcmp(dir, ".") == 0)
    {
        strcpy(changeto, cwd);
    }
    else if (strcmp(dir, "~") == 0)
    {
        strcpy(changeto, home);
    }
    else if(dir[0] == '~')
    {
        strcpy(changeto,home);
        strcat(changeto,&dir[1]);
    }
    else if (strcmp(dir, "..") == 0)
    {
        // if (strcmp(cwd, home) == 0)
        // {
        //     cd_home = 1;
        //     strcpy(changeto,cwd);
        //     strcpy(prev_dir, cwd);
        //     return;
        // }
        // else
        // {
        strcpy(changeto, "..");
        // }
    }
    else
    {
        strcpy(changeto, dir);
    }
    // printf("%s\n", dir);
    // printf("%s\n", changeto);

    if (chdir(changeto) < 0)
    {
        perror("No such directory exists\n");
        return;
    }
    strcpy(prev_dir, cwd);
    // cd_home = 0;
}
