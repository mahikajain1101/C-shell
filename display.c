#include "display.h"
#include "headers.h"
void display(void)
{
    char sysname[MAX];
    char name[MAX];
    getlogin_r(name,MAX);
    if (!name)
        perror("getlogin() error");
    else
    {
        gethostname(sysname, MAX);
        static int time1 = 1;
        char dir[MAX];
        char cwd[MAX];
        // char currdir[MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd() error");
            return;
        }
        // replace home as ~ in cwd
        int flag = 1;
        int len_home = strlen(home);
        int len_cwd = strlen(cwd);
       
        if (len_cwd >= len_home)
        {
            for (int i = 0; i < len_home; i++)
            {
                if (cwd[i] != home[i])
                {
                    flag = 0;
                }
            }
            if (flag)
            {
                cwd[0] = '~';
                for (int i = len_home; i <len_cwd ; i++)
                {
                    cwd[i - len_home + 1] = cwd[i];
                }
                cwd[len_cwd - len_home + 1] = '\0';
            }
        }
        printf("\033[0;31m");
        printf("<%s@%s:%s", name, sysname, cwd);
        if(total_time>1)
        {
            printf("took %ld sec",total_time);
        }
        printf("> ");
        printf("\033[0m");
    }
}