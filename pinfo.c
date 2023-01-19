#include "headers.h"
#include "pinfo.h"

void pinfo(int argc, char *argv[])
{
    char path[MAX];
    char pr_status[MAX];
    char ex_path[MAX];
    int pid;
    if (argc > 1)
    {
        perror("Too many arguments\n");
    }
    else if (argc == 0)
    {
        pid = getpid();
        strcpy(path, "/proc/self");
        strcpy(pr_status,"/proc/self");
        strcpy(ex_path,"/proc/self");
    }
    else
    {
        pid = atoi(argv[1]);
        strcpy(path, "/proc/");
        strcat(path, argv[1]);
        strcpy(pr_status, "/proc/");
        strcat(pr_status, argv[1]);
        strcpy(ex_path, "/proc/");
        strcat(ex_path, argv[1]);
    }
    strcat(path, "/stat");
    strcat(pr_status, "/status");
    strcat(ex_path, "/exe");
    char str_status[52];
    char str_mem[52];
    FILE *fptr;
    fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        perror("Error in opening the stat file\n");
        return;
    }
    else
    {
        char str[MAX];
        int a;
        int b;
        char *proc[MAX];
        fgets(str, MAX, fptr);
        // printf("%s\n",str);
        char *first = strtok(str, " ");
        // printf("aa\n");
        int d = 0;
        proc[0] = first;
        first = strtok(NULL, " ");
        while (first != NULL)
        {
            d++;
            proc[d] = first;
            first = strtok(NULL, " ");
        }
        strcpy(str_status, proc[2]);
        strcpy(str_mem, proc[22]);
        a = atoi(proc[4]);
        b = atoi(proc[7]);
        if (a == b)
        {
            str_status[1] = '+';
            str_status[2] = 0;
        }
        else
        {
            str_status[1] = 0;
        }
        fclose(fptr);
    }
    char ex_temp[MAX];
    int exe_len = readlink(ex_path, ex_temp, MAX);
    // printf("%s\n",ex_path);
    int flag = 1;
    if (exe_len >= 0)
    {
        int len_home = strlen(home);
        // printf("home = %s\n",home);
        int len_temp = strlen(ex_temp);
        // printf("temp = %s\n",ex_temp);
        if (len_home <= len_temp)
        {
            for (int i = 0; i < len_home; i++)
            {
                if (ex_temp[i] != home[i])
                {
                    flag = 0;
                }
            }
            // printf("flag = %d\n",flag);
            if (flag)
            {
                // printf("fwbbfjlwbf\n");
                ex_temp[0] = '~';
                for (int i = len_home; i < len_temp; i++)
                {
                    ex_temp[i - len_home + 1] = ex_temp[i];
                }
                ex_temp[len_temp - len_home + 1] = '\0';
            }
        }
    }
    else
    {
        perror("Error\n");
        return;
    }
    printf("pid : %d\n", pid);
    printf("process status : %s\n", str_status);
    printf("memory : %s {Virtual memory}\n", str_mem);
    printf("executable path : %s\n",ex_temp);
}