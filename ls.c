#include "headers.h"

void sortStrings(char arr[MAX][1000], int n)
{
    char temp[MAX];
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}
int is_regular_file(char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
int isDirectory(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
int isExec(char *path)
{
    struct stat sb;
    if (stat(path, &sb) == 0 && (sb.st_mode & S_IXUSR))
        return 1;
    return 0;
}

void permission_ls(char cwd[MAX])
{
    char perm[10];
    if (isDirectory(cwd))
        perm[0] = 'd';
    else
        perm[0] = '-';
    struct stat stats;
    stat(cwd, &stats);
    long long int p = stats.st_mode;

    for (long long int i = 0; i <= 8; i++)
    {
        if (((p >> i) % 2) == 0)
            perm[9 - i] = '-';
        else
        {
            char c;
            if (i % 3 == 0)
                c = 'x';
            else if (i % 3 == 1)
                c = 'w';
            else
                c = 'r';
            perm[9 - i] = c;
        }
    }
    printf("%s ", perm);
}

void print_ls(int all, char cwd[MAX], int l)
{
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
            if (!all)
            {
                if (dir_read->d_name[0] != '.')
                {
                    strcpy(ls_str[size++], dir_read->d_name);
                }
            }
            else
            {
                strcpy(ls_str[size++], dir_read->d_name);
            }
        }
        sortStrings(ls_str, size);
        if (l)
        {
            long int total = 0;
            for (int i = 0; i < size; i++)
            {
                char path[MAX];
                strcpy(path, changed);
                strcat(path, "/");
                strcat(path, ls_str[i]);
                struct stat stats;
                stat(path, &stats);
                total += stats.st_blocks;
            }
            total = total / 2;
            printf("total %ld\n", total);
        }
        for (int i = 0; i < size; i++)
        {
            char path[MAX];
            strcpy(path, changed);
            strcat(path, "/");
            strcat(path, ls_str[i]);
            if (l)
            {
                permission_ls(path);
                struct stat stats;
                stat(path, &stats);
                printf("%ld ", stats.st_nlink);
                struct passwd *f_pw = getpwuid(stats.st_uid);
                struct group *f_gr = getgrgid(stats.st_gid);
                printf("%s ", f_pw->pw_name);
                printf("%s ", f_gr->gr_name);
                printf("%6.ld ", stats.st_size);
                struct tm *time;
                char month_seq[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
                time = localtime(&(stats.st_mtime));
                printf("%s %02d %02d:%02d ", month_seq[time->tm_mon], time->tm_mday, time->tm_hour, time->tm_min);
            }
            if (isDirectory(path))
            {
                printf("\033[0;34m");
                printf("%s\n", ls_str[i]);
                printf("\033[0m");
            }
            else if (isExec(path))
            {
                printf("\033[0;32m");
                printf("%s\n", ls_str[i]);
                printf("\033[0m");
            }
            else if (is_regular_file(path))
            {
                printf("\033[0;37m");
                printf("%s\n", ls_str[i]);
                printf("\033[0m");
            }
        }
    }
    closedir(dir);
    chdir(current);
}

void ls(int argc, char *argv[])
{
    int aflag = 0;
    int lflag = 0;
    int noOfArguments = 0;
    for (int i = 0; i < argc; i++)
    {
        if (argv[i + 1][0] == '-')
        {
            if (argv[i + 1][1] == 'a' || argv[i + 1][2] == 'a')
                aflag = 1;
            if (argv[i + 1][1] == 'l' || argv[i + 1][2] == 'l')
                lflag = 1;
        }
        else
        {
            noOfArguments++;
        }
    }
    if (noOfArguments == 0)
    {

        char cwd[MAX];
        getcwd(cwd, MAX);
        if (aflag && lflag)
        {
            print_ls(1, cwd, 1);
        }
        else if (lflag)
        {
            print_ls(0, cwd, 1);
        }
        else if (aflag)
        {
            print_ls(1, cwd, 0);
        }
        else
        {
            print_ls(0, cwd, 0);
        }
    }
    else
    {
        char left[MAX][MAX];
        int num = 0;
        for (int i = 0; i < argc; i++)
        {
            if (argv[i + 1][0] == '-')
            {
                continue;
            }
            else
            {
                // printf("%s\n", argv[i + 1]);
                strcpy(left[num++], argv[i + 1]);
                // printf("aa\n");
            }
        }
        // printf("%d\n",num);
        for (int i = 0; i < num; i++)
        {
            // printf("left = %s\n", left[i]);
            if (left[i][0] == '~')
            {
                // printf("hoenwdo\n");
                char temp[MAX];
                strcpy(temp, home);
                strcat(temp, &left[i][1]);
                strcpy(left[i], temp);
            }
            if (is_regular_file(left[i]))
            {
                if (lflag)
                {
                    permission_ls(left[i]);
                    struct stat stats;
                    stat(left[i], &stats);
                    printf("%ld ", stats.st_nlink);
                    struct passwd *f_pw = getpwuid(stats.st_uid);
                    struct group *f_gr = getgrgid(stats.st_gid);
                    printf("%s ", f_pw->pw_name);
                    printf("%s ", f_gr->gr_name);
                    printf("%6.ld ", stats.st_size);
                    struct tm *time;
                    char months[][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
                    time = localtime(&(stats.st_mtime));

                    printf("%s %02d %02d:%02d ", months[time->tm_mon], time->tm_mday,
                           time->tm_hour, time->tm_min);
                }
                if (isExec(left[i]))
                {
                    printf("\033[0;32m");
                }
                printf("%s\n", left[i]);
                printf("\033[0;");
                // print_ls(0,argv[1],0);
            }
            else
            {
                if (aflag && lflag)
                {
                    printf("%s\n", left[i]);
                    print_ls(1, left[i], 1);
                }
                else if (aflag)
                {
                    print_ls(1, left[i], 0);
                }
                else if (lflag)
                {
                    printf("%s\n", left[i]);
                    print_ls(0, left[i], 1);
                }
                else
                {
                    print_ls(0, left[i], 0);
                }
            }
        }
    }
}