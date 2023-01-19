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
int fg_pid;
int list_size;
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
        char *ctrlD;
        ctrlD = fgets(command, MAX, stdin);
        if (ctrlD== NULL)
        {
            FILE *fptr2;
            char hist_file[MAX];
            strcpy(hist_file, home);
            strcat(hist_file, "/history.txt");
            fptr2 = fopen(hist_file, "w");
            write_hist(fptr2);
            printf("\n");
            exit(0);
        }
        signal(SIGINT,handler_c);
        signal(SIGTSTP,handler_z);
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
                pipe_(c, parameter, temp, flag_end, b);
                // execute(c,parameter,temp,flag_end,b);
                b--;
            }
            d--;
        }
        if (strcmp(command, "history") != 0)
            add_command(temp);
        strcpy(prev_cmd, temp);
    }
}