#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void handle_term();

int main()
{
	int i;
	unsigned sec=3;

	signal(SIGTERM, handle_term);

while(1) {
	alarm(sec);
	signal(SIGALRM, do_nothing);
	printf("vár...\n");
    i++;
	pause();
    }
}	
void do_nothing(){ ;}

void handle_term(int sig) {
	printf("%d\n",sig);
}
