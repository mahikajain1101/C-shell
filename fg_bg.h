#ifndef FG_H
#define FG_H
void fg(int argc,char* argv[],int bg);
void handler(int);
void insert(char command[1000], int key);
void insertFirst2(char command2[1000], int key,int n);
struct node *delete (int key);
struct node2 *delete2 (int key2);
extern time_t total_time;
struct node {
   char command[1000];
   int key;
   int index;
   struct node *next;
};
// struct node2 {
//    int n;
//    char command2[1000];
//    int key2;
//    struct node2 *next2;
// };
extern int bg_num;
extern struct node* head;
extern struct node* current;
extern int fg_pid;
extern int list_size;
// extern struct node2* head2;
// extern struct node2* current2;
#endif