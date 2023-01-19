#include "headers.h"

char prev_dir[MAX];
char home[MAX];
int total = 0;
char array[20][1000000];
char prev_cmd[MAX];
time_t total_time = 0;
int bg_num = 0;
struct node *head = NULL;
struct node *current = NULL;

int main()
{
    getcwd(home, MAX);
    FILE *fptr;
    fptr = fopen("history.txt", "r");
    if (fptr != NULL)
    {
        read_hist(fptr);
    }
    else
    {
        fptr = fopen("history.txt", "w");
    }
    fclose(fptr);
    while (1)
    {
        char temp[MAX];
        char command[MAX];
        display();
        total_time = 0;
        fgets(command, MAX, stdin);
        signal(SIGCHLD, handler);
        strcpy(temp, command);
        char *com_num[MAX];
        char *first = strtok(command, ";");
        int d = 0;
        com_num[0] = first;
        first = strtok(NULL, ";");
        while (first != NULL)
        {
            d++;
            com_num[d] = first;
            first = strtok(NULL, ";");
        }
        int e = d;
        while (d >= 0)
        {
            int amp = 0;
            for (int i = 0; i <= d; i++)
            {
                if (strcmp(com_num[i], "&") == 0)
                {
                    amp++;
                }
            }
            char *amp_num[MAX];
            char *second = strtok(com_num[e - d], "&");
            int b = 0;
            amp_num[0] = second;
            second = strtok(NULL, "&");
            while (second != NULL)
            {
                b++;
                amp_num[b] = second;
                second = strtok(NULL, "&");
            }
            int f = b;
            int flag_end;
            if ((b != 0) && (b == amp))
            {
                flag_end = 0;
            }
            else
            {
                flag_end = 1;
            }
            while (b >= 0)
            {
                // pipe_(f,amp_num);

                int c = 0;
                char *parameter[MAX];
                char *token = strtok(amp_num[f - b], " \t\n");
                parameter[0] = token;
                if (token == NULL)
                {
                    b--;
                    continue;
                }
                token = strtok(NULL, " \t\n");
                while (token != NULL)
                {
                    c++;
                    parameter[c] = token;
                    token = strtok(NULL, " \t\n");
                }
                parameter[c + 1] = NULL;
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
                            continue;;
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
                        if(flag1 && flag2)
                        {
                            // printf("ind1 = %d\n",stored_ind1);
                            // printf("ind2 = %d\n",stored_ind2);
                            if (i != stored_ind1 && i!= stored_ind1+1 && i != stored_ind2 && i != stored_ind2 + 1)
                            {
                                fin_param[num++] = parameter[i];
                            }
                        }
                        else if (flag1)
                        {
                            if (i != stored_ind1 && i!= stored_ind1+1)
                            {
                                fin_param[num++] = parameter[i];
                            }
                        }
                        else if(flag2)
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
                    for (int i = 0; i <=c; i++)
                    {
                        fin_param[num++] = parameter[i];
                    }
                }
                // printf("%d\n",num);
                fin_param[num] = NULL;
                // for(int i=0;i<num;i++)
                // {
                //     printf("%s\n",fin_param[i]);
                // }
                num = num-1;
                execute(num,fin_param,temp,flag_end,b,flag1,flag2,original1,original2);
                // char *com = fin_param[0];
                // if (strcmp(com, "cd") == 0)
                // {
                //     cd(num, fin_param);
                // }
                // else if (strcmp(com, "echo") == 0)
                // {
                //     echo(num, fin_param);
                // }
                // else if (strcmp(com, "pwd") == 0)
                // {
                //     pwd(num);
                // }
                // else if (strcmp(com, "pinfo") == 0)
                // {
                //     pinfo(num, fin_param);
                // }
                // else if (strcmp(com, "history") == 0)
                // {
                //     add_command(temp);
                //     history(num, fin_param);
                // }
                // else if (strcmp(com, "ls") == 0)
                // {
                //     ls(num, parameter);
                // }
                // else if (strcmp(com, "discover") == 0)
                // {
                //     discover(num, fin_param);
                // }
                // else if (strcmp(com, "exit") == 0)
                // {
                //     add_command(temp);
                //     FILE *fptr2;
                //     char hist_file[MAX];
                //     strcpy(hist_file, home);
                //     strcat(hist_file, "/history.txt");
                //     fptr2 = fopen(hist_file, "w");
                //     write_hist(fptr2);
                //     return (0);
                // }
                // else
                // {
                //     if (flag_end && (b == 0))
                //     {
                //         fg(num, fin_param, 0);
                //     }
                //     else
                //     {
                //         fg(num, fin_param, 1);
                //     }
                // }
                // // printf("dihwd\n");
                // if (flag1)
                // {
                //     // printf("aaaa\n");
                //     dup2(original1, STDIN_FILENO);
                //     // close()
                // }
                // if (flag2)
                // {
                //     dup2(original2, STDOUT_FILENO);
                // }
                b--;
            }
            d--;
        }
        if (strcmp(command, "history") != 0)
            add_command(temp);
        strcpy(prev_cmd, temp);
    }
}