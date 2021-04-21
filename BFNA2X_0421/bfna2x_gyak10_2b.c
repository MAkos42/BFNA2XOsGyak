#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf1 {
	long mtype;
	char mtext[512];
} rcvbuf, *msgp;

struct msqid_ds ds, *buf;

int main(){
    key_t key = ftok("msgkey",65);
    int msgflg = 00666 | IPC_CREAT | MSG_NOERROR;
    int msgid = msgget(key,msgflg);
    int msgsz = 32;
    int mtype = 0;

    msgp = &rcvbuf;
	buf = &ds;

    msgctl(msgid,IPC_STAT,buf);
    while (buf->msg_qnum) {
        printf("Hátralevő üzenetek száma: %ld\n",buf->msg_qnum);
    	msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
        printf("Üzenet: %s\n", msgp->mtext);
        msgctl(msgid,IPC_STAT,buf);
    }

    msgctl(msgid, IPC_RMID, NULL);
    printf("Üzenetsor törölve!\n");
}

