#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(){
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,64,0);
    char buf[64];

    char *mem = (char*) shmat(shmid,(void*)0,0);
    strcpy(buf,mem);

    printf("Szöveg: %s", buf);
    printf("Méret: %li\n", strlen(buf));

    shmdt(mem);
    shmctl(shmid,IPC_RMID,NULL);
}

