#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void do_nothing();


int main ()
{
	signal(SIGALRM, do_nothing);
    printf("%d\n", getpid());
	printf("vár...\n");
	pause();
    	printf("Alarm megérkezett\n");
}	
void do_nothing(){ ;}
