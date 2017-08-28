#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// ��Ϣ���нṹ
struct msg_form {
    long mtype;
    char mtext;
};

// �����壬����semctl��ʼ��
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};

// P����:
//  ���ź���ֵΪ1����ȡ��Դ�����ź���ֵ-1 
//  ���ź���ֵΪ0�����̹���ȴ�
int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*���*/
    sbuf.sem_op = -1; /*P����*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error");
        return -1;
    }
    return 0;
}

// V������
//  �ͷ���Դ�����ź���ֵ+1
//  ����н������ڹ���ȴ�����������
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; /*���*/
    sbuf.sem_op = 1;  /*V����*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}


int main()
{
    key_t key;
    int shmid, semid, msqid;
    char *shm;
    struct msg_form msg;
    int flag = 1; /*whileѭ������*/

    // ��ȡkeyֵ
    if((key = ftok(".", 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // ��ȡ�����ڴ�
    if((shmid = shmget(key, 1024, 0)) == -1)
    {
        perror("shmget error");
        exit(1);
    }

    // ���ӹ����ڴ�
    shm = (char*)shmat(shmid, 0, 0);
    if((int)shm == -1)
    {
        perror("Attach Shared Memory Error");
        exit(1);
    }

    // ������Ϣ����
    if ((msqid = msgget(key, 0)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    // ��ȡ�ź���
    if((semid = semget(key, 0, 0)) == -1)
    {
        perror("semget error");
        exit(1);
    }
    
    // д����
    printf("***************************************\n");
    printf("*                 IPC                 *\n");
    printf("*    Input r to send data to server.  *\n");
    printf("*    Input q to quit.                 *\n");
    printf("***************************************\n");
    
    while(flag)
    {
        char c;
        printf("Please input command: ");
        scanf("%c", &c);
        switch(c)
        {
            case 'r':
                printf("Data to send: ");
                sem_p(semid);  /*������Դ*/
                scanf("%s", shm);
                sem_v(semid);  /*�ͷ���Դ*/
                /*��ձ�׼���뻺����*/
                while((c=getchar())!='\n' && c!=EOF);
                msg.mtype = 888;  
                msg.mtext = 'r';  /*������Ϣ֪ͨ������������*/
                msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
                break;
            case 'q':
                msg.mtype = 888;
                msg.mtext = 'q';
                msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
                flag = 0;
                break;
            default:
                printf("Wrong input!\n");
                /*��ձ�׼���뻺����*/
                while((c=getchar())!='\n' && c!=EOF);
        }
    }

    // �Ͽ�����
    shmdt(shm);

    return 0;
}