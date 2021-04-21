#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {		
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

int main(){
    int msgsz;
    int msgflag = 00666|IPC_CREAT;
    key_t key = ftok("msgkey",65);
    int msgid = msgget(key,msgflag);

	msgp        = &sndbuf;
	msgp->mtype = 1;

 	strcpy(msgp->mtext,"BFNA2X");
	msgsz       = strlen(msgp->mtext) + 1;
    msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflag);

    printf("Első üzenet: \"%s\"\n", msgp->mtext);

 	strcpy(msgp->mtext,"Mészáros Ákos");
	msgsz       = strlen(msgp->mtext) + 1;
    msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflag);

    printf("Második üzenet: \"%s\"\n", msgp->mtext);
    return 0;
}
