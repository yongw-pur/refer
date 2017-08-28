 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/msg.h>
 
 // ���ڴ���һ��Ψһ��key
 #define MSG_FILE "/etc/passwd"
 
 // ��Ϣ�ṹ
 struct msg_form {
     long mtype;
     char mtext[256];
 };
 
 int main()
 {
     int msqid;
     key_t key;
     struct msg_form msg;
 
     // ��ȡkeyֵ
     if ((key = ftok(MSG_FILE, 'z')) < 0) 
     {
         perror("ftok error");
         exit(1);
     }
 
     // ��ӡkeyֵ
     printf("Message Queue - Client key is: %d.\n", key);
 
     // ����Ϣ����
     if ((msqid = msgget(key, IPC_CREAT|0777)) == -1) 
     {
         perror("msgget error");
         exit(1);
     }
 
     // ��ӡ��Ϣ����ID������ID
     printf("My msqid is: %d.\n", msqid);
     printf("My pid is: %d.\n", getpid());
 
     // �����Ϣ������Ϊ888
     msg.mtype = 888;
     sprintf(msg.mtext, "hello, I'm client %d", getpid());
     msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
 
     // ��ȡ����Ϊ777����Ϣ
     /*msgrcv(msqid, &msg, 256, 999, 0);
     printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
     printf("Client: receive msg.mtype is: %d.\n", msg.mtype);*/
     return 0;
 }