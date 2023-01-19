#include "headers.h"
void pipe_(int argc, char *argv[], char temp[], int flag_end, int b)
{
    char command[MAX][1000];
    int shell_stdout = dup(1);
    int shell_stdin = dup(0);
    int len = 0;
    for (int i = 0; i <= argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            int fildes[2];

            if (pipe(fildes) < 0)
            {
                perror("Could not create pipe.");
                exit(1);
            }
            if (dup2(fildes[1], 1) < 0)
            {
                perror("Error");
                return;
            }
            execute(len - 1, command, temp, flag_end, b);
            // dup2(shell_stdout, STDOUT_FILENO);

            if (dup2(fildes[0], 0) < 0)
            {
                perror("ERROR");
                return;
            }
            dup2(shell_stdout,1);
            // close(fildes[0]);
            for (int i = 0; i < len; i++)
            {
                // strcpy(command[i], "\0");
                // strcpy(command[i],NULL);
                command[i][0] = '\0';
            }
            len = 0;
        }
        else
        {
            strcpy(command[len++], argv[i]);
        }
    }
    close(STDOUT_FILENO);
    dup2(shell_stdout, 1);
    close(shell_stdout);
    execute(len - 1, command, temp, flag_end, b);
    // for(int i=0;i<len;i++)
    // {
    //     printf("%s\n",command[i]);
    // }
    close(STDIN_FILENO);
    dup2(shell_stdin, 0);
    close(shell_stdin);
}
