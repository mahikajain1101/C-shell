#include "headers.h"

int execute(int c, char parameter[][1000],char temp[],int flag_end,int b)
{
    // for(int i=0;i<c;i++)
    // {
    //     printf("%s\n",parameter[i]);
    // }
    int flag1 = 0;
    int flag2 = 0;
    int original1 = dup(STDIN_FILENO);
    // dup2(STDIN_FILENO, original1);
    int original2 = dup(STDOUT_FILENO);
    // dup2(STDOUT_FILENO, original2);
    int stored_ind1;
    int stored_ind2;
    for (int i = 0; i < c; i++)
    {
        if (strcmp(parameter[i], "<") == 0)
        {
            if (!flag1)
            {
                stored_ind1 = i;
            }
            flag1 = 1;
            if (i == -1)
            {
                perror("Error hai yeh");
                continue;
            }
            // printf("%s\n",parameter[i+1]);
            int fd = open(parameter[i + 1], O_RDONLY, 0);
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("Error in duplicating input file");
                continue;
            }
            // close(fd);
        }
        else if (strcmp(parameter[i], ">") == 0)
        {

            if (!flag2)
            {
                stored_ind2 = i;
            }
            flag2 = 1;
            if (i == -1)
            {
                perror("cdn");
                return 0;
            }
            int fd = open(parameter[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Error in duplicating input file");
                continue;
            }
            // close(fd);
        }
        else if (strcmp(parameter[i], ">>") == 0)
        {
            if (!flag2)
            {
                stored_ind2 = i;
            }
            flag2 = 1;
            if (i == -1)
            {
                perror("cdn");
                continue;
            }
            int fd = open(parameter[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Error in duplicating input file");
                continue;
            }
            // close(fd);
        }
    }
    // printf("kxnlas\n");
    char *fin_param[MAX];
    int num = 0;
    if (flag1 || flag2)
    {
        for (int i = 0; i <= c; i++)
        {
            if (flag1 && flag2)
            {
                // printf("ind1 = %d\n",stored_ind1);
                // printf("ind2 = %d\n",stored_ind2);
                if (i != stored_ind1 && i != stored_ind1 + 1 && i != stored_ind2 && i != stored_ind2 + 1)
                {
                    fin_param[num++] = parameter[i];
                }
            }
            else if (flag1)
            {
                if (i != stored_ind1 && i != stored_ind1 + 1)
                {
                    fin_param[num++] = parameter[i];
                }
            }
            else if (flag2)
            {
                if (i != stored_ind2 && i != stored_ind2 + 1)
                {
                    fin_param[num++] = parameter[i];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i <= c; i++)
        {
            fin_param[num++] = parameter[i];
        }
    }
    fin_param[num] = NULL;
    // for(int i=0;i<num;i++)
    // {
    //     printf("%s\n",fin_param[i]);
    // }
    num = num - 1;
    char *com = fin_param[0];
    if (strcmp(com, "cd") == 0)
    {
        cd(num, fin_param);
    }
    else if (strcmp(com, "echo") == 0)
    {
        echo(num, fin_param);
    }
    else if (strcmp(com, "pwd") == 0)
    {
        pwd(num);
    }
    else if (strcmp(com, "pinfo") == 0)
    {
        pinfo(num, fin_param);
    }
    else if (strcmp(com, "history") == 0)
    {
        add_command(temp);
        history(num, fin_param);
    }
    else if (strcmp(com, "ls") == 0)
    {
        ls(num, fin_param);
    }
    else if (strcmp(com, "discover") == 0)
    {
        discover(num, fin_param);
    }
    else if(strcmp(com,"jobs") == 0)
    {
        jobs(num,fin_param);
    }
    else if(strcmp(com,"sig") == 0)
    {
        sig(num,fin_param);
    }
    else if(strcmp(com,"fg") == 0)
    {
        fg_1(num,fin_param);
    }
    else if(strcmp(com,"bg") == 0)
    {
        bg_1(num,fin_param);
    }
    else if (strcmp(com, "exit") == 0)
    {
        add_command(temp);
        FILE *fptr2;
        char hist_file[MAX];
        strcpy(hist_file, home);
        strcat(hist_file, "/history.txt");
        fptr2 = fopen(hist_file, "w");
        write_hist(fptr2);
        exit(0);
    }
    else
    {
        if (flag_end && (b == 0))
        {
            // puts("hi");
            fg(num, fin_param, 0);
        }
        else
        {
            fg(num, fin_param, 1);
        }
    }
    if (flag1)
    {
        // printf("aaaa\n");
        dup2(original1, STDIN_FILENO);
        // close()
    }
    if (flag2)
    {
        dup2(original2, STDOUT_FILENO);
    }
    // printf("dihwd\n");
}