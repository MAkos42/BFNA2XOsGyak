#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{

    pid_t pid = getpid();
    key_t key = ftok("semkey",65);
	int semid = semget (key, 1, 00666 | IPC_CREAT);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}

    for (int i=0;i<3;i++)
	{
	  	down(semid);
        sleep(2);
	   	printf("PID: %d\n",pid);
        up(semid);
	   	val(semid);
	}

}


