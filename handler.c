#include "headers.h"

void handler(int sig)
{
   struct node *ptr = head;
   if (head == NULL)
   {
      return;
   }
   while (ptr != NULL)
   {
      int status;
      if (waitpid(ptr->key, &status, WNOHANG))
      {
         if (WIFEXITED(status))
         {
            // printf("%s with pid = %d exited normally\n", ptr->command, ptr->key);
            printf("\n%s with pid = %d exited normally\n", ptr->command, ptr->key);

         }
         else
         {
            printf("\n%s with pid = %d exited abnormally\n", ptr->command, ptr->key);
         }
         delete (ptr->key);
         bg_num--;
      }
      ptr = ptr->next;
   }
}


void handler_c(int sig)
{
   return ;
   // printf("admw\n");
   // if(sig == SIGINT)
   // {
   //    int pid = getpid();
   //    if(fg_pid == pid)
   //    {
   //       display();
   //       return;
   //    }
   //    kill(fg_pid, SIGINT);
   // }
   // printf("\b\b");
}

void handler_z(int signal)
{
   return;
}