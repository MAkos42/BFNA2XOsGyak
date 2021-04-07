#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void do_nothing();


int main ()
{
	signal(SIGALRM, do_nothing);
    printf("%d\n", getpid());
	printf("BFNA2X\n");
	pause();
    	printf("Alarm megérkezett\n");
}	
void do_nothing(){ ;}
