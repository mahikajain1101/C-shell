#include "pwd.h"
#include "headers.h"
void pwd(int num)
{
    char curr[MAX];
    getcwd(curr, MAX);
    printf("%s\n", curr);
}