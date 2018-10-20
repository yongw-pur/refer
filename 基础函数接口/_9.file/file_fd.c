/*************************
ͷ�ļ�
#include<unistd.h>
int dup (int oldfd)
����˵��:���Ʋ���oldfd��ָ���ļ������ʣ����������ء�
         �µ��ļ������ʺ�oldfdָ��ͬһ���ļ����������е���������дλ�ú͸���Ȩ�޻���ꡣ���ļ�������֮�䲢������close-on-exec���
         ���磬������lseek()��ĳ���ļ�����������ʱ����һ���ļ������ʵĶ�дλ��Ҳ�����Ÿı䡣
����:�����Ƴɹ�ʱ���򷵻���С����δʹ�õ��ļ������ʡ�
     ���д����򷵻�-1��errno���Ŵ�����롣�������EBADF����fd����Ч���ļ������ʣ�����ļ��ѹر�
close(1);
fd2=dup(fd1); //���ص�һ����1����Ϊ�չرձ�׼���������������ݲ�������������ʾ�������������ʾ��1.txt�У�1.txt�ļ��ͱ�׼����Ͱ������ˣ������Ժ��������׼�������Ϣ�Ϳ��Ե�1.txt�в鿴
�����׼����������Ǵ򿪵��ļ�,��д�����ݶ����û����ƣ�����д���ĵط����Ķ�. fd 0 1 2 �ֱ��ʾ ��׼���룬��׼�������׼���󡣺����������

ͷ�ļ�
#include<unistd.h>
#include<fcntl.h>
int fcntl(int fd, int cmd, ...)//int fcntl(int fd,int cmd,long arg) int fcntl(int fd,int cmd,struct flock * lock)
����˵��:�����ļ�������������
         ����cmd:
            F_DUPFD�������ļ�������
            F_DUPFD_CLOEXEC�������ļ������������ļ���������������close-on-exec
            F_GETFD����ȡ�ļ�������ʶ
            F_SETFD ����close-on-exec ��ꡣ������Բ���arg��FD_CLOEXECλ������
            F_GETFL ȡ���ļ�������״̬��꣬�����Ϊopen�Ĳ���flags��
            F_SETFL �����ļ�������״̬��꣬����argΪ����꣬��ֻ����O_APPEND��O_NONBLOCK��O_ASYNCλ�ĸı䣬����λ�ĸı佫����Ӱ�졣
            F_GETLK ȡ���ļ�������״̬��
            F_SETLK �����ļ�������״̬����ʱflcok�ṹ��l_type ֵ������F_RDLCK��F_WRLCK��F_UNLCK������޷������������򷵻�-1���������ΪEACCES ��EAGAIN��
            F_SETLKW F_SETLK ������ͬ�������޷���������ʱ���˵��û�һֱ�ȵ����������ɹ�Ϊֹ�����ڵȴ������Ĺ����б��ź��ж�ʱ������������-1���������ΪEINTR
         ����lockָ��Ϊflock �ṹָ��
            struct flcok
            {
                short int l_type; //������״̬ F_RDLCK ����һ������ȡ�õ�����; F_WRLCK ����һ����д���õ�����; F_UNLCK ɾ��֮ǰ����������
                short int l_whence;//����l_startλ�� SEEK_SET ���ļ���ͷΪ��������ʼλ��; SEEK_CUR ��Ŀǰ�ļ���дλ��Ϊ��������ʼλ�� SEEK_END ���ļ���βΪ��������ʼλ��
                off_t l_start; //��������Ŀ�ͷλ��
                off_t l_len; //��������Ĵ�С
                pid_t l_pid; //���������Ľ���
            };
����:get�����ɹ�����flag,arg����Ϊ0

ͷ�ļ�
#include<sys/file.h>
int flock(int fd,int operation)
����˵��:flock()����operationָ����ʽ�Բ���fd��ָ���ļ����������������Ķ�����
         �˺���ֻ�����������ļ����޷������ļ���ĳһ����
         ����operation
            LOCK_SH ��������������������̿�ͬʱ��ͬһ���ļ��������������ж���û�м�����0(����)
            LOCK_EX ��������������һ���ļ�ͬʱֻ��һ���������� (0 == flock(fd, LOCK_EX)�ܻ�ȡ��)(д��)
            LOCK_UN ����ļ�����״̬��
            LOCK_NB �޷���������ʱ���˲����ɲ�����ϣ����Ϸ��ؽ��̡�ͨ����LOCK_SH��LOCK_EX ��(|)���
            i = flock(fd, LOCK_SH | LOCK_NB)�ж��Ƿ������ʹ��dup()��fork()ʱ�ļ������ʲ���̳д����������ڼ��˶���������£���д���ǲ��ɹ���
����:0��ʾ�ɹ������д����򷵻�-1������������errno

ͷ�ļ�
#include<stdio.h>
FILE * fdopen(int fildes,const char * mode)
����˵��:������fildes���ļ�������(fd)��ת��Ϊ��Ӧ���ļ�ָ��󷵻�
         mode �ַ�����������ļ�ָ�������̬������̬�����ԭ���ļ������ʶ�дģʽ��ͬ(�ο�fopen)


**************************/
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    FILE *f = fopen("temp", "w+");
    if (!f)
    {
        printf("error file\n");
        return;
    }

    if(0 == flock(fileno(f), LOCK_EX))
    {
        printf("lock...\n");
        getchar();
        fclose(f);
        flock(fileno(f), LOCK_UN);
    }
    else
    {
        printf("lock failed\n");
    }
    /*�������״̬
    int i = flock(fileno(f), LOCK_EX | LOCK_NB);
    printf("i %d\n", i);*/

    FILE *fp = fdopen(0,"w+");
    fprintf(fp,"%s\n", "hello!");
    fclose(fp);
}


/**************
���Խ��
****************/

/***************
ͬ���ͺ���:
int dup2(int odlfd,int newfd)//���Ʋ���oldfd��ָ���ļ������ʣ�����������������newfd��һ�鷵�ء�������newfdΪһ�Ѵ򿪵��ļ������ʣ���newfd��ָ���ļ����ȱ��ر�
                             dup2()�൱�ڵ���fcntl(oldfd��F_DUPFD��newfd),���غ�dup��ͬ
int fileno(FILE * stream) //��ò���streamָ�����ļ�����ʹ�õ��ļ�������
***************/

