#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

	struct sembuf sembuf, *sop; 
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;
	int cmd;

int main()
{
    key_t key = ftok("semkey",65);
	int semid = semget (key, 1, 00666 | IPC_CREAT);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}

	int semnum = 0;

	cmd = SETVAL;
	semctl(semid,0, SETVAL, 1);
	printf("semid: %d\n",semid);
}
