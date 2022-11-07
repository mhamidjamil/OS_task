#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define SIZE 512
struct msgbuf {
  long mtype;
  char mtext[SIZE];
};
int main() {
  key_t key;
  key = 9999;
  int qid;
  qid = msgget(key, IPC_CREAT | 0666);
  struct msgbuf msg1;
  msg1.mtype = 10;
  strcpy(msg1.mtext, "Message queue using ipc\n");
  msgsnd(qid, &msg1, sizeof msg1.mtext, 0);
  struct msgbuf msg2;
  msg2.mtype = 20;
  strcpy(msg2.mtext, "Message queue with ipc and Message\n");
  msgsnd(qid, &msg2, sizeof msg2.mtext, 0);

  return 0;
}
