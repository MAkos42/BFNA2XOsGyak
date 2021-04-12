#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>

volatile int stop;
volatile int waitp;
volatile int waitc;
void handle_int();
void handle_usrp();
void handle_usrc();

int main(){
    int parent, child;
    FILE* fd;
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,32,0666|IPC_CREAT);


    parent = getpid();
    child = fork();

    if(child == 0){
        char buf[32];
        char *mem = (char*) shmat(shmid,(void*)0,0);
        fd = fopen("bfna2x_in.txt", "r");
        if(!fd){
            perror("fopen(\"r\") hiba!");
            kill(parent, SIGKILL);
            exit(-1);
        }
        signal(SIGUSR1, handle_usrp);
        fgets(buf, sizeof(buf), fd);
        
        printf("%s",buf);

        while(fgets(buf,sizeof(buf),fd)){
            printf("%s",buf);
            strcpy(mem, buf);
            kill(parent, SIGUSR1);
            while(!waitp){;}
            waitp = 0;
        }

        shmdt(mem);
        fclose(fd);
        kill(parent, SIGINT);
        
    }


    if(child > 0){
        int n1, n2;
        char *mem = (char*) shmat(shmid,(void*)0,0);
        char str[50];
        char *token;
        fd = fopen("bfna2x_out.txt", "w");
        if(!fd){
            perror("fopen(\"w\") hiba!");
            kill(child, SIGKILL);
            exit(-1);
        }
        signal(SIGINT, handle_int);
        signal(SIGUSR1, handle_usrc);
        
        while(!stop){
            while(!waitc){;}
            waitc = 0;
            if(stop) break;
            strcpy(str, mem);
            kill(child, SIGUSR1);

            token = strtok(str," ");
            n1 = atoi(token);
            token = strtok(NULL, " ");
            n2 = atoi(token);

            fprintf(fd, "%d %d ", n1, n2);
            while(n1!=n2){
                if(n1 > n2)
                    n1 -= n2;
                else
                    n2 -= n1;
            }
            fprintf(fd, "%d\n", n1);
        }
        shmdt(mem);
        fclose(fd);
        shmctl(shmid,IPC_RMID,NULL);
    }
}

void handle_int(){
    stop = 1;
    waitp = 1;
    waitc = 1;
}
void handle_usrp(){
    waitp = 1;
    printf("read finished %d\n", waitp);
}
void handle_usrc(){
    waitc = 1;
    printf("write finished %d\n", waitc);
}

