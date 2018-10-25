/*************************
头文件
#include<stdlib.h>
int atexit (void (*function)(void))
函数说明:设置程序正常结束前调用的函数;当程序通过调用exit()或从main中返回时，参数function所指定的函数会先被调用，然后exit结束程序
返回:成功则返回0，否则返回-1，失败原因存于errno中

头文件
#include<unistd.h>
int execl(const char *path, const char *arg,...)
函数说明:执行参数path命令，arg代表执行该文件时传递过去的argv(0)、argv[1]，第一个参数为命令名称(argv[0])，最后一个参数必须用空指针(NULL)作结束
返回:成功则函数不会返回，执行失败则直接返回-1
    当进程调用一种execl函数时，该进程完全由新程序代换，而新程序则从其main函数开始执行
    因为调用exec并不创建新进程，所以前后的进程ID并未改变。exec只是用另一个新程序替换了当前进程的正文、数据、堆和栈段
    当前进程的正文都被替换了，execl后的语句，即便execl退出了，都不会被执行

int execlp(const char *file,const char *arg,...)
函数说明:从PATH环境变量所指的目录中查找符合参数file的文件名，
         将第二个以后的参数当做该文件的argv[0]、argv[1]…最后一个参数必须用空指针(NULL)作结束

int execv(const char *path, char *const argv[])
函数说明:执行参数path命令，利用数组指针来传递参数给执行文件

头文件:
#include<unistd.h>
#include<sys/types.h>
pid_t fork( void);
函数说明:fork函数创建一个新进程。由fork创建的新进程被称为子进程（child process）。fork函数被调用一次但返回两次。两次返回的唯一区别是子进程中返回0值而父进程中返回子进程ID
         子进程是父进程的副本，它将获得父进程数据空间、堆、栈等资源的副本,存储空间独立
父进程退出后，子进程接收到信号
signal(SIGHUP, handle_signal);
prctl(PR_SET_PDEATHSIG,SIGHUP);

头文件:
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait (int *status)
函数说明:暂时停止目前进程的执行，直到有信号来到或子进程结束。如果在调用wait()时子进程已经结束，则wait()会立即返回子进程结束状态值。子进程的结束状态值会由参数status返回，
         而子进程的进程识别码也会一快返回。如果不在意结束状态值，status可以设成NULL
返回:如果执行成功则返回子进程识别码(PID)，如果有错误发生则返回-1
多个子进程处理情况
while (1) {
    ret = wait(NULL);
    if (ret == -1) {
        if (errno == EINTR) 
        {   // 返回值为-1的时候有两种情况，一种是没有子进程了，还有一种是被中断了
            continue;
        }
        break;
    }
}

pid_t waitpid(pid_t pid,int *status,int options)
函数说明:同wait, 参数pid为欲等待的子进程识别码
        pid<-1 等待进程组识别码为pid绝对值的任何子进程
        pid=-1 等待任何子进程，相当于wait()
        pid=0 等待进程组识别码与目前进程相同的任何子进程
        pid>0 等待任何子进程识别码为pid的子进程
    参数option可以为0 或下面的OR 组合
        WNOHANG 如果没有任何已经结束的子进程则马上返回，不予以等待
        WUNTRACED 如果子进程进入暂停执行情况则马上返回，但结束状态不予以理会
    子进程的结束状态返回后存于status，底下有几个宏可判别结束情况
    WIFEXITED(status)如果子进程正常结束则为非0值。
    WEXITSTATUS(status)取得子进程exit()返回的结束代码，一般会先用WIFEXITED来判断是否正常结束才能使用此宏。
    WIFSIGNALED(status)如果子进程是因为信号而结束则此宏值为真
    WTERMSIG(status)取得子进程因信号而中止的信号代码，一般会先用WIFSIGNALED来判断后才使用此宏。
    WIFSTOPPED(status)如果子进程处于暂停执行情况则此宏值为真。一般只有使用WUNTRACED 时才会有此情况。
    WSTOPSIG(status)取得引发子进程暂停的信号代码，一般会先用WIFSTOPPED 来判断后才使用此宏
返回:如果执行成功则返回子进程识别码(PID)，如果有错误发生则返回-1

pid_t getpid(void);
函数说明:取得目前进程的进程识别码

头文件
#include<sys/time.h>
#include<sys/resource.h>
int getpriority(int which,int who)
函数说明:取得进程、进程组和用户的进程执行优先权   
    which who代表的意义
    PRIO_PROCESS who为进程识别码
    PRIO_PGRP who为进程的组识别码
    PRIO_USER who为用户识别码
返回:进程执行优先权,-20 至20之间,数值越低代表有较高的优先次序，执行会较频繁

**************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

void my_exit(void)//后调用
{
    printf("my_exit!\n");
}

void my_para_exit(int status,void *arg) //先调用
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
测试结果
****************/

/***************
同类型函数:
int execve(const char *filename,char *const argv[],char *const envp[])//executes the program pointed to by filename
             内核级系统调用，参数filename字符串所代表的文件路径，第二个参数系利用数组指针来传递给执行文件，最后一个参数则为传递给执行文件的新环境变量数组
int execvp(const char *file ,char * const argv [])//从PATH环境变量所指的目录中查找符合参数file的文件名，argv为参数表 execlp
int on_exit(void (* function)(int, void*),void *arg)//设置一个程序正常结束前调用的函数,参数arg指针会传给参数function函数
void exit(int status)//正常终结目前进程的执行，并把参数status返回给父进程，而进程所有的缓冲区数据会自动写回并关闭未关闭的文件
void _exit(int status)//立刻结束目前进程的执行，并把参数status返回给父进程，并关闭未关闭的文件。
                    传递SIGCHLD信号给父进程，父进程可以由wait函数取得子进程结束状态
pid_t vfork(void)//vfork保证子进程先运行，它调用exec或exit后父进程才能调度运行
pid_t getpgid(pid_t pid)//取得参数pid指定进程所属的组识别码。如果参数pid为0，则会取得目前进程的组识别码
                 一个进程可以属于某个进程组。可以发送信号给一组进程. 进程组id = 父进程id
pid_t getpgrp(void)//取得目前进程所属的组识别码
int setpgid(pid_t pid,pid_t pgid)//将参数pid 指定进程所属的组识别码设为参数pgid指定的组识别码
             如果参数pid 为0，则会用来设置目前进程的组识别码，如果参数pgid为0，则会以目前进程的进程识别码来取代。
int setpgrp(void)//将目前进程所属的组识别码设为目前进程的进程识别码
int nice(int inc)//改变进程的进程执行优先顺序。参数inc数值越大则优先顺序排在越后面，即表示进程执行会越慢。只有超级用户才能使用负的inc 值
int setpriority(int which,int who, int prio)//设置进程、进程组和用户的进程执行优先权
***************/

