/*
ʹ���ˡ������ڴ�+�ź���+��Ϣ���С��������ʵ�ַ�����������ͻ����̼��ͨ�š�
�����ڴ������������ݣ�
�ź�������ͬ����
��Ϣ�������� �ڿͻ����޸��˹����ڴ�� ֪ͨ��������ȡ��
��Դ�ڣ�http://www.cnblogs.com/CheeseZH/p/5264465.html
*/


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

// ��ʼ���ź���
int init_sem(int sem_id, int value)
{
    union semun tmp;
    tmp.val = value;
    if(semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

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

// ɾ���ź�����
int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error");
        return -1;
    }
    return 0;
}

// ����һ���ź�����
int creat_sem(key_t key)
{
    int sem_id;
    if((sem_id = semget(key, 1, IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(-1);
    }
    init_sem(sem_id, 1);  /*��ֵ��Ϊ1��Դδռ��*/
    return sem_id;
}


int main()
{
    key_t key;
    int shmid, semid, msqid;
    char *shm;
    char data[] = "this is server";
    struct shmid_ds buf1;  /*����ɾ�������ڴ�*/
    struct msqid_ds buf2;  /*����ɾ����Ϣ����*/
    struct msg_form msg;  /*��Ϣ��������֪ͨ�Է������˹����ڴ�*/

    // ��ȡkeyֵ
    if((key = ftok(".", 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // ���������ڴ�
    if((shmid = shmget(key, 1024, IPC_CREAT|0666)) == -1)
    {
        perror("Create Shared Memory Error");
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
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    // �����ź���
    semid = creat_sem(key);
    
    // ������
    while(1)
    {
        msgrcv(msqid, &msg, 1, 888, 0); /*��ȡ����Ϊ888����Ϣ*/
        if(msg.mtext == 'q')  /*quit - ����ѭ��*/ 
            break;
        if(msg.mtext == 'r')  /*read - �������ڴ�*/
        {
            sem_p(semid);
            printf("%s\n",shm);
            sem_v(semid);
        }
    }

    // �Ͽ�����
    shmdt(shm);

    /*ɾ�������ڴ桢��Ϣ���С��ź���*/
    shmctl(shmid, IPC_RMID, &buf1);
    msgctl(msqid, IPC_RMID, &buf2);
    del_sem(semid);
    return 0;
}