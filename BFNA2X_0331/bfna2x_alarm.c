#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void handle_int();

int main ()
{
	int i;
	unsigned sec=1;

	signal(SIGINT, handle_int);

for (i=1;i<8;i++) {
	alarm(sec);
	signal(SIGALRM, do_nothing);
	printf("vár... x%d\n",i);
	pause();
    }
}	
void do_nothing(){ ;}

void handle_int() {
	printf("interrupt signal érkezett\n");
	signal(SIGINT,SIG_IGN);
}
