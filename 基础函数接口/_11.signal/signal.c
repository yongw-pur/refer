/*************************
ͷ�ļ�
#include<unistd.h>
unsigned int alarm(unsigned int seconds)
����˵��:�����ź�SIGALRM�ھ�������secondsָ�����������͸�Ŀǰ�Ľ���
         �������seconds Ϊ0����֮ǰ���õ����ӻᱻȡ��������ʣ�µ�ʱ�䷵��
����:����֮ǰ���ӵ�ʣ�����������֮ǰδ�������򷵻�0

ͷ�ļ�:
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid,int sig)
����˵��:�Ͳ���sigָ�����źŸ�����pidָ���Ľ���    
        ����pid�м������:
        pid>0 ���źŴ�������ʶ����Ϊpid �Ľ��̡�
        pid=0 ���źŴ�����Ŀǰ������ͬ����������н���
        pid=-1 ���źŹ㲥���͸�ϵͳ�����еĽ���
        pid<0 ���źŴ���������ʶ����Ϊpid����ֵ�����н���
        �������ź�:
        SIGHUP 1 A �ն˹�����߿��ƽ�����ֹ
        SIGINT 2 A �����жϣ���break�������£�
        SIGQUIT 3 C ���̵��˳���������
        SIGILL 4 C �Ƿ�ָ��
        SIGABRT 6 C ��abort(3)�������˳�ָ��
        SIGFPE 8 C �����쳣
        SIGKILL 9 AEF Kill�ź�
        SIGSEGV 11 C ��Ч���ڴ�����
        SIGPIPE 13 A �ܵ�����: дһ��û�ж��˿ڵĹܵ�
        SIGALRM 14 A ��alarm(2)�������ź�
        SIGTERM 15 A ��ֹ�ź�
        SIGUSR1 30,10,16 A �û��Զ����ź�1
        SIGUSR2 31,12,17 A �û��Զ����ź�2
        SIGCHLD 20,17,18 B �ӽ��̽����ź�
        SIGCONT 19,18,25 ���̼���������ֹͣ�Ľ��̣�
        SIGSTOP 17,19,23 DEF ��ֹ����
        SIGTSTP 18,20,24 D �����նˣ�tty���ϰ���ֹͣ��
        SIGTTIN 21,21,26 D ��̨������ͼ�ӿ����ն˶�
        SIGTTOU 22,22,27 D ��̨������ͼ�ӿ����ն�д
        SIGBUS 10,7,10 C ���ߴ���(������ڴ����)
        SIGPOLL A Sys V�����Pollable�¼�����SIGIOͬ��
����:ִ�гɹ��򷵻�0������д����򷵻�-1

int pause(void)
����˵��:��ǰ�Ľ�����ͣ������˯��״̬����ֱ�����ź�(signal)���ж�
����ֵ:ֻ����-1

unsigned int sleep(unsigned int seconds)
����˵��:��Ŀǰ�Ľ�����ͣ��ֱ���ﵽ����seconds ��ָ����ʱ�䣬���Ǳ��ź����ж�
����:��������ͣ������seconds ��ָ����ʱ���򷵻�0�������ź��ж��򷵻�ʣ������

void perror(const char *s)
����˵��:����һ���������������ԭ���������׼����(stderr)
         ����s��ָ���ַ������ȴ�ӡ���������ټ��ϴ���ԭ���ַ������˴���ԭ������ȫ�ֱ���errno��ֵ������Ҫ������ַ���

ͷ�ļ�
#include<sys/types.h>
#include<sys/stat.h>
int mkfifo(const char * pathname,mode_t mode)
����˵��:���ݲ���pathname���������FIFO�ļ������ļ����벻���ڣ�����modeΪ���ļ���Ȩ��(mask 0666)
         mkfifo������FIFO�ļ��������̶������ö�дһ���ļ��ķ�ʽ��ȡ
            open��FIFO�ļ�ʱ��O_NONBLOCK������Ӱ��
            1����ʹ��O_NONBLOCK ���ʱ����FIFO �ļ�����ȡ�Ĳ��������̷��أ���������û���������̴�FIFO �ļ�����ȡ����д��Ĳ����᷵��ENXIO ������롣
            2��û��ʹ��O_NONBLOCK ���ʱ����FIFO ����ȡ�Ĳ�����ȵ��������̴�FIFO�ļ���д����������ء�ͬ���أ���FIFO�ļ���д��Ĳ�����ȵ��������̴�FIFO �ļ�����ȡ�����������
����:���ɹ��򷵻�0�����򷵻�-1������ԭ�����errno��

int pipe(int filedes[2])
����˵��:�����ܵ��������ļ��������ɲ���filedes���鷵�ء�filedes[0]Ϊ�ܵ���Ķ�ȡ�ˣ�filedes[1]��Ϊ�ܵ���д���
����:���ɹ��򷵻��㣬���򷵻�-1������ԭ�����errno��

FILE * popen( const char * command,const char * type)
����˵��:����fork()�����ӽ��̣�Ȼ����ӽ����е���/bin/sh -c��ִ�в���command��ָ�����type��ʹ��"r"�����ȡ��"w"����д��
         ���̿����ô��ļ�ָ������ȡ�ӽ��̵�����豸����д�뵽�ӽ��̵ı�׼�����豸�С����⣬����ʹ���ļ�ָ��(FILE*)�����ĺ���Ҳ������ʹ�ã�����fclose()���⡣
����:���ɹ��򷵻��ļ�ָ�룬���򷵻�NULL

int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact)
����˵��:���ݲ���signumָ�����źű�������ø��źŵĴ�����������signum����ָ��SIGKILL��SIGSTOP����������ź�
        struct sigaction
        {
            void (*sa_handler) (int);
            sigset_t sa_mask;
            int sa_flags;
            void (*sa_restorer) (void);
        }
        sa_handler�˲�����signal()�Ĳ���handler��ͬ�������µ��źŴ�����������������ο�signal()��
        sa_mask ���������ڴ�����ź�ʱ��ʱ��sa_maskָ�����źŸ��á�
                �ڵ��ø��źŲ�׽����֮ǰ����һ�źż�Ҫ�ӵ����̵��ź��������С��������źŲ�׽��������ʱ�ٽ����̵��ź������ָ�λΪԭ��ֵ��
                �������ڵ����źŴ������ʱ��������ĳЩ�ź�
                һ�����̵��ź������ֹ涨�˵�ǰ���������ܵ��͸��ý��̵��źż�
        sa_restorer �˲���û��ʹ�á�
        sa_flags ���������źŴ����������ز���(��OR����)     
            A_NOCLDSTOP : �������signumΪSIGCHLD�����ӽ�����ͣʱ������֪ͨ������
            SA_ONESHOT/SA_RESETHAND:�źŴ�����һ�������ù��ͻָ���Ĭ�ϵ��źŴ�����ȥ����ʹ��sa_handler=SIG_DFL
            SA_RESTART:���ź��жϵ�ϵͳ���û���������
            SA_NODEFER:���źŴ��������ڽ���ʱ�������������źŴ����������źŹ��� (ִ���źŴ������Ĺ����У��ٴθ���ctrl+c�źŵ�ʱ�򣬻ᵼ���ٴε����źŴ�����)
            SA_RESETHAND:���û�ע����źŴ�������ִ�й�һ�κ󣬸��źŵĴ���������ΪϵͳĬ�ϵĴ�����
            act.sa_flags = 0;��ִ���źŴ���������ڼ䣬��β���ctrl+c������Ҳ��������źŴ������������ڱ����źŴ��������֮����ִ��һ���źŴ�����������ǰ������˶��ٴ�ctrl+c�źţ�
        �������oldact����NULLָ�룬��ԭ�����źŴ���ʽ���ɴ˽ṹsigaction ���ء�
����:ִ�гɹ��򷵻�0������д����򷵻�-1

int sigaddset(sigset_t *set,int signum)
����˵��:������signum ������źż���������set �źż���
����:ִ�гɹ��򷵻�0������д����򷵻�-1

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler)
����˵��:���ݲ���signumָ�����źű�������ø��źŵĴ���������ָ�����źŵ���ʱ�ͻ���ת������handlerָ���ĺ���ִ��
         �������handler���Ǻ���ָ�룬�������������������֮һ:
            SIG_IGN ���Բ���signumָ�����źš�
            SIG_DFL ������signum ָ�����ź�����Ϊ����Ԥ����źŴ���
         ���źŷ�����ת���Զ���handler������ִ�к�ϵͳ���Զ����˴���������ԭ��ϵͳԤ��Ĵ���ʽ�����Ҫ�ı�˲��������sigaction()

int sigprocmask(int how,const sigset_t *set,sigset_t * oldset)
����˵��:�ı�Ŀǰ���ź����֣������������how������     
        SIG_BLOCK �µ��ź�������Ŀǰ���ź����ֺͲ���set ָ�����ź�����������
        SIG_UNBLOCK ��Ŀǰ���ź�����ɾ��������setָ�����ź�����
        SIG_SETMASK ��Ŀǰ���ź�������ɲ���setָ�����ź����֡�
        �������oldset����NULLָ�룬��ôĿǰ���ź����ֻ��ɴ�ָ�뷵��
����: ִ�гɹ��򷵻�0������д����򷵻�-1

**************************/
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void handler(int num) 
{
    printf("hello\n");
}

void show_handler(int num)
{
    switch (num)
    {
        case SIGUSR1:
            printf("SIGUSR\n");
            break;
        case SIGALRM:
            printf("SIGALRM\n");
            break;
        default: printf("%d\n", num);
    } 
}

main()
{
    int i;

    signal(SIGALRM,handler);
    alarm(5);
    
    for(i=1;i<7;i++)
    {
        printf("sleep %d ...\n",i);
        sleep(1);
    }


    struct sigaction act,oldact;
    act.sa_handler = show_handler;
    act.sa_flags = SA_ONESHOT|SA_NOMASK;
    sigaction(SIGUSR1, &act, &oldact);
    for(i=5;i<15;i++)
    {
        sigaction(i,NULL,&oldact);
        printf("sa_handler of signal %2d = %p\n",i, oldact.sa_handler);
    }

#if 0
    alarm(5);
    for(i=1;i<7;i++)
    {
        printf("sleep %d ...\n",i);
        sleep(1);
    }
#endif
}


/**************
���Խ��
sleep 1 ...
sleep 2 ...
sleep 3 ...
sleep 4 ...
sleep 5 ...
hello
sleep 6 ...
sa_handler of signal  5 = (nil)
sa_handler of signal  6 = (nil)
sa_handler of signal  7 = (nil)
sa_handler of signal  8 = (nil)
sa_handler of signal  9 = (nil)
sa_handler of signal 10 = 0x8048521
sa_handler of signal 11 = (nil)
sa_handler of signal 12 = (nil)
sa_handler of signal 13 = (nil)
sa_handler of signal 14 = 0x804850d
****************/

/***************
ͬ���ͺ���:
int sigemptyset(sigset_t *set)//������set�źż���ʼ�������
int sigdelset(sigset_t * set,int signum)//������signum������źŴӲ���set�źż���ɾ��
int sigfillset(sigset_t * set)//������set�źż���ʼ����Ȼ������е��źż��뵽���źż���
int sigismember(const sigset_t *set,int signum)//���Բ���signum������ź��Ƿ��Ѽ���������set�źż��
                 ����źż������и��ź��򷵻�1��û���򷵻�0������д����򷵻�-1
int sigpending(sigset_t *set)//�������õ��źż����ɲ���setָ�뷵��
char * strerror(int errnum)//����errnum�Ĵ����������ѯ�����ԭ��������ַ�����Ȼ�󽫸��ַ���ָ�뷵��#include<string.h>
int pclose(FILE * stream)//�ر���popen�������Ĺܵ����ļ�ָ��,�����ӽ��̵Ľ���״̬������д����򷵻�-1������ԭ�����errno��
�����ǰ���ctrl+c��ʱ�򣬲���Ϊ����ϵͳ����SIGINT�źţ�SIGINT�źŵ�Ĭ�ϴ����˳�����
�����ǰ���ctrl+/��ʱ�򣬲���Ϊ����ϵͳ����SIGQUIT�źţ����źŵ�Ĭ�ϴ���Ϊ�˳�����
***************/

