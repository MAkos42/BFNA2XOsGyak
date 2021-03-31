#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void handle_int();
void handle_quit(int sig);


int main ()
{
    signal(SIGQUIT, handle_quit);
    signal(SIGINT, handle_int);
    while(1);
    return 0;
}
void handle_quit(int sig){
   printf("Quit signal %d\n", sig);
    exit(0); 
}

void handle_int(){
    printf("Interrupt signal elkapva\n");
    signal(SIGINT, SIG_DFL);
}

