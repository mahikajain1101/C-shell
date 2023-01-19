#include "headers.h"
void swap(struct node *a, struct node *b) 
{ 
    char temp[MAX];
    strcpy(temp,a->command); 
    strcpy(a->command,b->command); 
    strcpy(b->command,temp);
    int temp1;
    temp1 =  a->key;
    a->key = b->key;
    b->key = temp1;
    int temp2;
    temp2 = a->index;
    a->index = b->index;
    b->index = temp2;
} 
void bubbleSort(struct node *start) 
{ 
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (strcmp(ptr1->command,ptr1->next->command)>0) 
            { 
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}
void jobs(int argc, char *argv[])
{
    if (argc == 0)
    {
        // int i = 0;
        struct node *ptr = head;
        bubbleSort(head);
        while (ptr != NULL)
        {

            int bg_pid = ptr->key;
            char file[MAX];
            sprintf(file, "/proc/%d/stat", bg_pid);
            FILE *fptr;
            fptr = fopen(file, "r");
            if (fptr == NULL)
            {
                perror("Error in opening the stat file\n");
                return;
            }
            else
            {
                char status;
                char fin_stat[MAX];
                fscanf(fptr, "%*d %*s %c", &status);
                if (status == 'T')
                {
                    strcpy(fin_stat, "Stopped");
                }
                else 
                {
                    strcpy(fin_stat, "Running");
                }
                printf("[%d] %s %s [%d]\n", ptr->index, fin_stat, ptr->command, ptr->key);
            }
            // i++;
            ptr = ptr->next;
        }
    }
    else if (argc == 1)
    {
        if (strcmp(argv[1], "-r") == 0)
        {
            // int i = 0;
            struct node *ptr = head;
            while (ptr != NULL)
            {

                int bg_pid = ptr->key;
                char file[MAX];
                sprintf(file, "/proc/%d/stat", bg_pid);
                FILE *fptr;
                fptr = fopen(file, "r");
                if (fptr == NULL)
                {
                    perror("Error in opening the stat file\n");
                    return;
                }
                else
                {
                    char status;
                    fscanf(fptr, "%*d %*s %c", &status);
                    if (status != 'T')
                    {
                        printf("[%d] %s %s [%d]\n", ptr->index, "Running", ptr->command, ptr->key);
                    }
                    // i++;
                    ptr = ptr->next;
                }
            }
        }
        if (strcmp(argv[1], "-s") == 0)
        {
            // int i = 0;
            struct node *ptr = head;
            while (ptr != NULL)
            {

                int bg_pid = ptr->key;
                char file[MAX];
                sprintf(file, "/proc/%d/stat", bg_pid);
                FILE *fptr;
                fptr = fopen(file, "r");
                if (fptr == NULL)
                {
                    perror("Error in opening the stat file\n");
                    return;
                }
                else
                {
                    char status;
                    fscanf(fptr, "%*d %*s %c", &status);
                    if (status == 'T')
                    {
                        printf("[%d] %s %s [%d]\n", ptr->index, "Stopped", ptr->command, ptr->key);
                    }
                    // i++;
                    ptr = ptr->next;
                }
            }
        }
    }
}
void sig(int argc, char *argv[])
{
    int pid_num = atoi(argv[1]);
    // printf("%d\n",pid_num);
    int sig = atoi(argv[2]);
    struct node *temp = head;
    // int i = 1;
    while (1)
    {
        if (temp->index == pid_num)
        {
            int pid = temp->key;
            if (kill(pid, sig) < 0)
            {
                perror("Error in killing");
                return;
            }
            return;
        }
        if (temp == NULL)
        {
            perror("No job with the given number exist");
            return;
        }
        temp = temp->next;
        // i++;
    }
}
void fg_1(int argc, char *argv[])
{
    int pid_num = atoi(argv[1]);
    struct node *temp = head;
    // int i = 1;
    while (1)
    {
        if (temp->index == pid_num)
        {
            int pid = temp->key;
            int status;
            delete (pid);
            setpgid(pid, getpgid(0));
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, pid);
            if (kill(pid, SIGCONT) < 0)
            {
                perror("Error");
            }
            waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(0, getpgid(0));
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            if (WIFSTOPPED(status))
                return;
            return;
        }
        if (temp == NULL)
        {
            perror("No job with the given number exist");
            return;
        }
        temp = temp->next;
        // i++;
    }
}
void bg_1(int argc, char *argv[])
{
    int pid_num = atoi(argv[1]);
    struct node *temp = head;
    // int i = 1;
    while (1)
    {
        if (temp->index == pid_num)
        {
            int pid = temp->key;
            char file[MAX];
            sprintf(file, "/proc/%d/stat", pid);
            FILE *fptr;
            fptr = fopen(file, "r");
            if (fptr == NULL)
            {
                perror("Error in opening the stat file\n");
                return;
            }
            else
            {
                char status;
                char fin_stat[MAX];
                fscanf(fptr, "%*d %*s %c", &status);
                if (status == 'T')
                {
                    printf("aa\n");
                    if (kill(pid, SIGCONT) < 0)
                    {
                        perror("Error");
                    }
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        if (temp == NULL)
        {
            perror("No job with the given number exist");
            return;
        }
        temp = temp->next;
        // i++;
    }
}