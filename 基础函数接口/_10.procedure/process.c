/*************************
ͷ�ļ�
#include<stdlib.h>
int atexit (void (*function)(void))
����˵��:���ó�����������ǰ���õĺ���;������ͨ������exit()���main�з���ʱ������function��ָ���ĺ������ȱ����ã�Ȼ��exit��������
����:�ɹ��򷵻�0�����򷵻�-1��ʧ��ԭ�����errno��

ͷ�ļ�
#include<unistd.h>
int execl(const char *path, const char *arg,...)
����˵��:ִ�в���path���arg����ִ�и��ļ�ʱ���ݹ�ȥ��argv(0)��argv[1]����һ������Ϊ��������(argv[0])�����һ�����������ÿ�ָ��(NULL)������
����:�ɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1
    �����̵���һ��execl����ʱ���ý�����ȫ���³�����������³��������main������ʼִ��
    ��Ϊ����exec���������½��̣�����ǰ��Ľ���ID��δ�ı䡣execֻ������һ���³����滻�˵�ǰ���̵����ġ����ݡ��Ѻ�ջ��
    ��ǰ���̵����Ķ����滻�ˣ�execl�����䣬����execl�˳��ˣ������ᱻִ��

int execlp(const char *file,const char *arg,...)
����˵��:��PATH����������ָ��Ŀ¼�в��ҷ��ϲ���file���ļ�����
         ���ڶ����Ժ�Ĳ����������ļ���argv[0]��argv[1]�����һ�����������ÿ�ָ��(NULL)������

int execv(const char *path, char *const argv[])
����˵��:ִ�в���path�����������ָ�������ݲ�����ִ���ļ�

ͷ�ļ�:
#include<unistd.h>
#include<sys/types.h>
pid_t fork( void);
����˵��:fork��������һ���½��̡���fork�������½��̱���Ϊ�ӽ��̣�child process����fork����������һ�ε��������Ρ����η��ص�Ψһ�������ӽ����з���0ֵ���������з����ӽ���ID
         �ӽ����Ǹ����̵ĸ�����������ø��������ݿռ䡢�ѡ�ջ����Դ�ĸ���,�洢�ռ����
�������˳����ӽ��̽��յ��ź�
signal(SIGHUP, handle_signal);
prctl(PR_SET_PDEATHSIG,SIGHUP);

ͷ�ļ�:
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait (int *status)
����˵��:��ʱֹͣĿǰ���̵�ִ�У�ֱ�����ź��������ӽ��̽���������ڵ���wait()ʱ�ӽ����Ѿ���������wait()�����������ӽ��̽���״ֵ̬���ӽ��̵Ľ���״ֵ̬���ɲ���status���أ�
         ���ӽ��̵Ľ���ʶ����Ҳ��һ�췵�ء�������������״ֵ̬��status�������NULL
����:���ִ�гɹ��򷵻��ӽ���ʶ����(PID)������д������򷵻�-1
����ӽ��̴������
while (1) {
    ret = wait(NULL);
    if (ret == -1) {
        if (errno == EINTR) 
        {   // ����ֵΪ-1��ʱ�������������һ����û���ӽ����ˣ�����һ���Ǳ��ж���
            continue;
        }
        break;
    }
}

pid_t waitpid(pid_t pid,int *status,int options)
����˵��:ͬwait, ����pidΪ���ȴ����ӽ���ʶ����
        pid<-1 �ȴ�������ʶ����Ϊpid����ֵ���κ��ӽ���
        pid=-1 �ȴ��κ��ӽ��̣��൱��wait()
        pid=0 �ȴ�������ʶ������Ŀǰ������ͬ���κ��ӽ���
        pid>0 �ȴ��κ��ӽ���ʶ����Ϊpid���ӽ���
    ����option����Ϊ0 �������OR ���
        WNOHANG ���û���κ��Ѿ��������ӽ��������Ϸ��أ������Եȴ�
        WUNTRACED ����ӽ��̽�����ִͣ����������Ϸ��أ�������״̬���������
    �ӽ��̵Ľ���״̬���غ����status�������м�������б�������
    WIFEXITED(status)����ӽ�������������Ϊ��0ֵ��
    WEXITSTATUS(status)ȡ���ӽ���exit()���صĽ������룬һ�������WIFEXITED���ж��Ƿ�������������ʹ�ô˺ꡣ
    WIFSIGNALED(status)����ӽ�������Ϊ�źŶ�������˺�ֵΪ��
    WTERMSIG(status)ȡ���ӽ������źŶ���ֹ���źŴ��룬һ�������WIFSIGNALED���жϺ��ʹ�ô˺ꡣ
    WIFSTOPPED(status)����ӽ��̴�����ִͣ�������˺�ֵΪ�档һ��ֻ��ʹ��WUNTRACED ʱ�Ż��д������
    WSTOPSIG(status)ȡ�������ӽ�����ͣ���źŴ��룬һ�������WIFSTOPPED ���жϺ��ʹ�ô˺�
����:���ִ�гɹ��򷵻��ӽ���ʶ����(PID)������д������򷵻�-1

pid_t getpid(void);
����˵��:ȡ��Ŀǰ���̵Ľ���ʶ����

ͷ�ļ�
#include<sys/time.h>
#include<sys/resource.h>
int getpriority(int which,int who)
����˵��:ȡ�ý��̡���������û��Ľ���ִ������Ȩ   
    which who���������
    PRIO_PROCESS whoΪ����ʶ����
    PRIO_PGRP whoΪ���̵���ʶ����
    PRIO_USER whoΪ�û�ʶ����
����:����ִ������Ȩ,-20 ��20֮��,��ֵԽ�ʹ����нϸߵ����ȴ���ִ�л��Ƶ��

**************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

void my_exit(void)//�����
{
    printf("my_exit!\n");
}

void my_para_exit(int status,void *arg) //�ȵ���
{
    printf("exit (%d)\n",status);
    printf("arg = %s\n",(char*)arg);
}


main()
{
    
    /*char *argv[ ]={"ls", "-al", "/etc/passwd", 0};
    char * envp[ ]={"PATH=/bin", 0};
    execve("/bin/ls", argv, envp);
    execv("/bin/ls",argv);
    execl("/bin/ls","ls","-al","/etc/passwd",(char * )0);
    execlp("ls","ls","-al","/etc/passwd",(char *)0);*/

    pid_t pid=fork();
    if(pid < 0)
    {
        fprintf(stderr,"fork err");
    }
    else if(pid == 0)//child process
    {
        printf("child process %d !\n", getpid());
        execl("/bin/ls","ls","-al","/etc/passwd",(char * )0);
        exit(0);
    }
    else
    {
        printf("father process %d\n",pid);
    }

    atexit (my_exit);
    on_exit(my_para_exit,"on exit");
    exit(0);
}


/**************
���Խ��
****************/

/***************
ͬ���ͺ���:
int execve(const char *filename,char *const argv[],char *const envp[])//executes the program pointed to by filename
             �ں˼�ϵͳ���ã�����filename�ַ�����������ļ�·�����ڶ�������ϵ��������ָ�������ݸ�ִ���ļ������һ��������Ϊ���ݸ�ִ���ļ����»�����������
int execvp(const char *file ,char * const argv [])//��PATH����������ָ��Ŀ¼�в��ҷ��ϲ���file���ļ�����argvΪ������ execlp
int on_exit(void (* function)(int, void*),void *arg)//����һ��������������ǰ���õĺ���,����argָ��ᴫ������function����
void exit(int status)//�����ս�Ŀǰ���̵�ִ�У����Ѳ���status���ظ������̣����������еĻ��������ݻ��Զ�д�ز��ر�δ�رյ��ļ�
void _exit(int status)//���̽���Ŀǰ���̵�ִ�У����Ѳ���status���ظ������̣����ر�δ�رյ��ļ���
                    ����SIGCHLD�źŸ������̣������̿�����wait����ȡ���ӽ��̽���״̬
pid_t vfork(void)//vfork��֤�ӽ��������У�������exec��exit�󸸽��̲��ܵ�������
pid_t getpgid(pid_t pid)//ȡ�ò���pidָ��������������ʶ���롣�������pidΪ0�����ȡ��Ŀǰ���̵���ʶ����
                 һ�����̿�������ĳ�������顣���Է����źŸ�һ�����. ������id = ������id
pid_t getpgrp(void)//ȡ��Ŀǰ������������ʶ����
int setpgid(pid_t pid,pid_t pgid)//������pid ָ��������������ʶ������Ϊ����pgidָ������ʶ����
             �������pid Ϊ0�������������Ŀǰ���̵���ʶ���룬�������pgidΪ0�������Ŀǰ���̵Ľ���ʶ������ȡ����
int setpgrp(void)//��Ŀǰ������������ʶ������ΪĿǰ���̵Ľ���ʶ����
int nice(int inc)//�ı���̵Ľ���ִ������˳�򡣲���inc��ֵԽ��������˳������Խ���棬����ʾ����ִ�л�Խ����ֻ�г����û�����ʹ�ø���inc ֵ
int setpriority(int which,int who, int prio)//���ý��̡���������û��Ľ���ִ������Ȩ
***************/

