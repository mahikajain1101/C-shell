#include "echo.h"
#include "headers.h"

void echo(int argc, char *parameter[])
{
    for (int i = 1; i <= argc; i++)
    {
        printf("%s ", parameter[i]);
    }
    printf("\n");
}