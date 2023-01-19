#include "headers.h"

void insert(char comm[1000], int key)
{
   struct node *ptr = (struct node *)malloc(sizeof(struct node));
   strcpy(ptr->command, comm);
   
   ptr->key = key;
   ptr->next = NULL;
   struct node *temp;
   // while(temp->next != NULL)
   // {
   //    temp = temp->next;
   // }
   // temp->next = ptr;
   if (head == NULL)
   {
      list_size = 1;
      ptr->index = 1;
      ptr->next = NULL;
      head = ptr;
   }
   else
   {
      list_size++;
      ptr->index = list_size;
      temp = head;
      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = ptr;
      ptr->next = NULL;
   }
}
struct node *delete (int key)
{
   struct node *current = head;
   struct node *previous = NULL;
   if (head == NULL)
   {
      return NULL;
   }
   while (current->key != key)
   {
      if (current->next == NULL)
      {
         return NULL;
      }
      else
      {
         previous = current;
         current = current->next;
      }
   }
   if (current == head)
   {
      head = head->next;
   }
   else
   {
      previous->next = current->next;
   }
   return current;
}

void fg(int argc, char *argv[], int bg)
{
   pid_t proc_id = fork();
   // argv[argc] = NULL;
   if (proc_id < 0)
   {
      perror("Error in getting process id\n");
      return;
   }
   else if (proc_id == 0)
   {
      setpgid(0, 0);

      if (execvp(argv[0], argv) < 0)
      {
         kill(proc_id, SIGTERM);
      }
   }
   else if (proc_id > 0)
   {
      if (bg)
      {
         bg_num++;
         printf("[%d]   %d\n", bg_num, proc_id);
         char pass[MAX];
         strcpy(pass, argv[0]);
         if (argc == 1)
         {
            // printf("aa\n");
            strcat(pass, " ");
            strcat(pass, argv[1]);
         }
         // printf("%s\n",pass);
         insert(pass, proc_id);
      }
      else
      {
         fg_pid = proc_id;
         time_t begin = time(NULL);
         int status;
         signal(SIGTTIN, SIG_IGN);
         signal(SIGTTOU, SIG_IGN);
         tcsetpgrp(0, proc_id);
         waitpid(proc_id, &status, WUNTRACED);
         tcsetpgrp(0, getpgid(0));
         signal(SIGTTIN, SIG_DFL);
         signal(SIGTTOU, SIG_DFL);
         if (WIFSTOPPED(status))
         {
            char pass[MAX];
            strcpy(pass, argv[0]);
            if (argc == 1)
            {
               strcat(pass, " ");
               strcat(pass, argv[1]);
            }
            insert(pass, proc_id);
         }
         time_t end = time(NULL);
         total_time += end - begin;
      }
   }
}