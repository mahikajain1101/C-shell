#include "headers.h"

void print_dis(char cwd[MAX], int fflag, int dflag, char dot[MAX], char file[MAX])
{
    int flag = 0;
    char current[MAX];
    getcwd(current, MAX);
    if (chdir(cwd) < 0)
    {
        perror("No such directory\n");
        return;
    }
    char changed[MAX];
    getcwd(changed, MAX);
    DIR *dir;
    struct dirent *dir_read;
    char ls_str[MAX][1000];
    dir = opendir(changed);
    if (dir != NULL)
    {
        int size = 0;
        while ((dir_read = readdir(dir)) != NULL)
        {
            if (dir_read->d_name[0] != '.')
            {
                strcpy(ls_str[size++], dir_read->d_name);
            }
        }
        for (int i = 0; i < size; i++)
        {
            if (file != NULL)
            {
                flag = 1;
                if (strcmp(ls_str[i], file) == 0)
                {

                    flag = 2;
                    char path[MAX];
                    strcpy(path, changed);
                    strcat(path, "/");
                    strcat(path, ls_str[i]);
                    char final[MAX];
                    strcpy(final, dot);
                    strcat(final, "/");
                    strcat(final, ls_str[i]);
                    if (dflag && !fflag)
                    {
                        if (isDirectory(path))
                        {
                            printf("%s\n", final);
                        }
                    }
                    else if (fflag && !dflag)
                    {
                        if (is_regular_file(path))
                        {
                            printf("%s\n", final);
                        }
                    }
                    else
                    {
                        printf("%s\n", final);
                    }
                }
            }
            char path[MAX];
            strcpy(path, changed);
            strcat(path, "/");
            strcat(path, ls_str[i]);
            char final[MAX];
            strcpy(final, dot);
            strcat(final, "/");
            strcat(final, ls_str[i]);
            if (!flag)
            {
                if (dflag && !fflag)
                {
                    if (isDirectory(path))
                    {
                        printf("%s\n", final);
                    }
                }
                else if (fflag && !dflag)
                {
                    if (is_regular_file(path))
                    {
                        printf("%s\n", final);
                    }
                }
                else
                {
                    printf("%s\n", final);
                }
            }
            if (!is_regular_file(path))
            {
                char temp[MAX];
                strcpy(temp, dot);
                strcat(temp, "/");
                strcat(temp, ls_str[i]);
                print_dis(path, fflag, dflag, temp, file);
            }
        }
    }
    closedir(dir);
    chdir(current);
}

void discover(int argc, char *argv[])
{
    int dflag = 0;
    int fflag = 0;
    char str[2] = {'"'};
    char tilde[MAX];
    if (argc > 0)
    {
        if (argv[1][0]=='~')
        {
            char temp[MAX];
            strcpy(temp, home);
            strcat(temp, &argv[1][1]);
            strcpy(tilde, temp);
            
        }
        else{
            strcpy(tilde,argv[1]);
        }
    }
    if (argc == 0)
    {
        char cwd[MAX];
        getcwd(cwd, MAX);
        printf(".\n");
        print_dis(cwd, 0, 0, ".", NULL);
    }
    else if (argc == 1)
    {
        if (isDirectory(tilde))
        {
            printf("%s\n", tilde);
            print_dis(tilde, 0, 0, argv[1], NULL);
        }
        else if (strcmp(argv[1], "-d") == 0)
        {
            dflag = 1;
            char cwd[MAX];
            getcwd(cwd, MAX);
            printf(".\n");
            print_dis(cwd, 0, 1, ".", NULL);
        }
        else if (strcmp(argv[1], "-f") == 0)
        {
            fflag = 1;
            char cwd[MAX];
            getcwd(cwd, MAX);
            printf(".\n");
            print_dis(cwd, 1, 0, ".", NULL);
        }
        else
        {
            char *token = strtok(argv[1], str);
            // printf("%s\n", token);
            print_dis(".", 0, 0, ".", token);
        }
    }
    else if (argc == 2)
    {
        if (isDirectory(tilde))
        {
            if (strcmp(argv[2], "-f") == 0)
            {
                fflag = 1;
                print_dis(tilde, 1, 0, argv[1], NULL);
            }
            else if (strcmp(argv[2], "-d") == 0)
            {
                printf("%s\n", argv[1]);
                dflag = 1;
                print_dis(tilde, 0, 1, argv[1], NULL);
            }
            else
            {
                char *token = strtok(argv[2], str);
                print_dis(tilde, 0, 0, argv[1], token);
            }
        }
        else if ((strcmp(argv[1], "-f") == 0 && strcmp(argv[2], "-d") == 0) || strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-f") == 0)
        {
            char cwd[MAX];
            getcwd(cwd, MAX);
            printf(".\n");
            print_dis(cwd, 0, 0, ".", NULL);
        }
        else
        {
            if (strcmp(argv[1], "-f") == 0)
            {
                char *token = strtok(argv[2], str);
                print_dis(".", 1, 0, ".", token);
            }
            if (strcmp(argv[1], "-d") == 0)
            {
                char *token = strtok(argv[2], str);
                print_dis(".", 0, 1, ".", token);
            }
        }
    }
    else if (argc == 3)
    {
        // printf("bb\n");
        if (isDirectory(tilde))
        {
            // printf("aa\n");
            if ((strcmp(argv[2], "-f") == 0 && strcmp(argv[3], "-d") == 0) || (strcmp(argv[2], "-d") == 0 && strcmp(argv[3], "-f") == 0))
            {
                // printf("dxnkwnd\n");
                printf("%s\n", argv[1]);
                print_dis(tilde, 0, 0, argv[1], NULL);
            }
            else if (strcmp(argv[2], "-f") == 0)
            {
                fflag = 1;
                if (strcmp(argv[3], "-d") != 0)
                {
                    char *token = strtok(argv[3], str);
                    print_dis(tilde, 1, 0, argv[1], token);
                }
            }
            else if (strcmp(argv[2], "-d") == 0)
            {
                dflag = 1;
                if (strcmp(argv[3], "-f") != 0)
                {
                    char *token = strtok(argv[3], str);
                    // printf("%s\n", argv[1]);
                    print_dis(tilde, 0, 1, argv[1], token);
                }
            }
        }
        else
        {
            char *token = strtok(argv[3], str);
            print_dis(".", 0, 0, ".", token);
        }
    }
    else
    {
        if (isDirectory(tilde))
        {
            if ((strcmp(argv[2], "-d") == 0 && strcmp(argv[3], "-f") == 0) || (strcmp(argv[2], "-d") == 0 && strcmp(argv[3], "-f") == 0))
            {
                char *token = strtok(argv[4], str);
                print_dis(tilde, 0, 0, argv[1], token);
            }
        }
    }
}