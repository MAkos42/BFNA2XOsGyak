#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(){
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,64,0666|IPC_CREAT);
    char buf[64] = "BFNA2X\n";

    char *mem = (char*) shmat(shmid,(void*)0,0);

    strcpy(mem, buf);

    printf("Memóriába írva: %s", buf);

    shmdt(mem);
}
