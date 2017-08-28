#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// ���ڴ���һ��Ψһ��key
#define MSG_FILE "/etc/passwd"

// ��Ϣ�ṹ
struct msg_form {
    long mtype; //�������������
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;
    
    // ��ȡkeyֵ
    if((key = ftok(MSG_FILE,'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // ��ӡkeyֵ
    printf("Message Queue - Server key is: %d.\n", key);

    // ������Ϣ����
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    // ��ӡ��Ϣ����ID������ID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // ѭ����ȡ��Ϣ
	msgrcv(msqid, &msg, sizeof(msg.mtext), 888, 0);// ��������Ϊ888�ĵ�һ����Ϣ
	printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
	printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);

	/*msg.mtype = 999; // �ͻ��˽��յ���Ϣ����
	sprintf(msg.mtext, "hello, I'm server %d", getpid());
	msgsnd(msqid, &msg, sizeof(msg.mtext), 0);*/

	if(msgctl(msqid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(-1);  
    }  
    return 0;
}

/*˵��
ʹ��ftok��ȡ��ֵ
��һ���UNIXʵ���У��ǽ��ļ��������ڵ��ȡ����ǰ���������ŵõ�key_t�ķ���ֵ��
��ָ���ļ��������ڵ��Ϊ65538�������16����Ϊ0x010002������ָ����IDֵΪ38�������16����Ϊ0x26��������key_t����ֵΪ0x26010002��
���Ҫȷ��key_tֵ���䣬Ҫôȷ��ftok���ļ�����ɾ����Ҫô����ftok��ָ��һ���̶���key_tֵ
*/