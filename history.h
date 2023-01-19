#ifndef HISTORY_C
#define HISTORY_C
void history(int,char**);
void add_command(char*);
void write_hist(FILE*);
void read_hist(FILE*);
extern char array[20][1000000];
extern int total;
extern char prev_cmd[1000];
#endif