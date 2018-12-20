/*************************
头文件
#include<unistd.h>
unsigned int alarm(unsigned int seconds)
函数说明:设置信号SIGALRM在经过参数seconds指定的秒数后传送给目前的进程
         如果参数seconds 为0，则之前设置的闹钟会被取消，并将剩下的时间返回
返回:返回之前闹钟的剩余秒数，如果之前未设闹钟则返回0

头文件:
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid,int sig)
函数说明:送参数sig指定的信号给参数pid指定的进程    
        参数pid有几种情况:
        pid>0 将信号传给进程识别码为pid 的进程。
        pid=0 将信号传给和目前进程相同进程组的所有进程
        pid=-1 将信号广播传送给系统内所有的进程
        pid<0 将信号传给进程组识别码为pid绝对值的所有进程
        常见的信号:
        SIGHUP 1 A 终端挂起或者控制进程终止
        SIGINT 2 A 键盘中断（如break键被按下）
        SIGQUIT 3 C 键盘的退出键被按下
        SIGILL 4 C 非法指令
        SIGABRT 6 C 由abort(3)发出的退出指令
        SIGFPE 8 C 浮点异常
        SIGKILL 9 AEF Kill信号
        SIGSEGV 11 C 无效的内存引用
        SIGPIPE 13 A 管道破裂: 写一个没有读端口的管道
        SIGALRM 14 A 由alarm(2)发出的信号
        SIGTERM 15 A 终止信号
        SIGUSR1 30,10,16 A 用户自定义信号1
        SIGUSR2 31,12,17 A 用户自定义信号2
        SIGCHLD 20,17,18 B 子进程结束信号
        SIGCONT 19,18,25 进程继续（曾被停止的进程）
        SIGSTOP 17,19,23 DEF 终止进程
        SIGTSTP 18,20,24 D 控制终端（tty）上按下停止键
        SIGTTIN 21,21,26 D 后台进程企图从控制终端读
        SIGTTOU 22,22,27 D 后台进程企图从控制终端写
        SIGBUS 10,7,10 C 总线错误(错误的内存访问)
        SIGPOLL A Sys V定义的Pollable事件，与SIGIO同义
返回:执行成功则返回0，如果有错误则返回-1

int pause(void)
函数说明:当前的进程暂停（进入睡眠状态），直到被信号(signal)所中断
返回值:只返回-1

unsigned int sleep(unsigned int seconds)
函数说明:让目前的进程暂停，直到达到参数seconds 所指定的时间，或是被信号所中断
返回:若进程暂停到参数seconds 所指定的时间则返回0，若有信号中断则返回剩余秒数

void perror(const char *s)
函数说明:将上一个函数发生错误的原因输出到标准错误(stderr)
         参数s所指的字符串会先打印出，后面再加上错误原因字符串。此错误原因依照全局变量errno的值来决定要输出的字符串

头文件
#include<sys/types.h>
#include<sys/stat.h>
int mkfifo(const char * pathname,mode_t mode)
函数说明:根据参数pathname建立特殊的FIFO文件，该文件必须不存在，参数mode为该文件的权限(mask 0666)
         mkfifo建立的FIFO文件其他进程都可以用读写一般文件的方式存取
            open打开FIFO文件时，O_NONBLOCK旗标会有影响
            1、当使用O_NONBLOCK 旗标时，打开FIFO 文件来读取的操作会立刻返回，但是若还没有其他进程打开FIFO 文件来读取，则写入的操作会返回ENXIO 错误代码。
            2、没有使用O_NONBLOCK 旗标时，打开FIFO 来读取的操作会等到其他进程打开FIFO文件来写入才正常返回。同样地，打开FIFO文件来写入的操作会等到其他进程打开FIFO 文件来读取后才正常返回
返回:若成功则返回0，否则返回-1，错误原因存于errno中

int pipe(int filedes[2])
函数说明:建立管道，并将文件描述词由参数filedes数组返回。filedes[0]为管道里的读取端，filedes[1]则为管道的写入端
返回:若成功则返回零，否则返回-1，错误原因存于errno中

FILE * popen( const char * command,const char * type)
函数说明:调用fork()产生子进程，然后从子进程中调用/bin/sh -c来执行参数command的指令。参数type可使用"r"代表读取，"w"代表写入
         进程可利用此文件指针来读取子进程的输出设备或是写入到子进程的标准输入设备中。此外，所有使用文件指针(FILE*)操作的函数也都可以使用，除了fclose()以外。
返回:若成功则返回文件指针，否则返回NULL

int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact)
函数说明:根据参数signum指定的信号编号来设置该信号的处理函数。参数signum可以指定SIGKILL和SIGSTOP以外的所有信号
        struct sigaction
        {
            void (*sa_handler) (int);
            sigset_t sa_mask;
            int sa_flags;
            void (*sa_restorer) (void);
        }
        sa_handler此参数和signal()的参数handler相同，代表新的信号处理函数，其他意义请参考signal()。
        sa_mask 用来设置在处理该信号时暂时将sa_mask指定的信号搁置。
                在调用该信号捕捉函数之前，这一信号集要加到进程的信号屏蔽字中。仅当从信号捕捉函数返回时再将进程的信号屏蔽字复位为原先值。
                这样，在调用信号处理程序时就能阻塞某些信号
                一个进程的信号屏蔽字规定了当前阻塞而不能递送给该进程的信号集
        sa_restorer 此参数没有使用。
        sa_flags 用来设置信号处理的其他相关操作(可OR操作)     
            A_NOCLDSTOP : 如果参数signum为SIGCHLD，则当子进程暂停时并不会通知父进程
            SA_ONESHOT/SA_RESETHAND:信号处理函数一旦被调用过就恢复到默认的信号处理函数去，即使得sa_handler=SIG_DFL
            SA_RESTART:被信号中断的系统调用会自行重启
            SA_NODEFER:当信号处理函数正在进行时，不堵塞对于信号处理函数自身信号功能 (执行信号处理函数的过程中，再次给予ctrl+c信号的时候，会导致再次调用信号处理函数)
            SA_RESETHAND:当用户注册的信号处理函数被执行过一次后，该信号的处理函数被设为系统默认的处理函数
            act.sa_flags = 0;在执行信号处理函数这段期间，多次操作ctrl+c，程序也不会调用信号处理函数，而是在本次信号处理函数完成之后，在执行一次信号处理函数（无论前面产生了多少次ctrl+c信号）
        如果参数oldact不是NULL指针，则原来的信号处理方式会由此结构sigaction 返回。
返回:执行成功则返回0，如果有错误则返回-1

int sigaddset(sigset_t *set,int signum)
函数说明:将参数signum 代表的信号加入至参数set 信号集里
返回:执行成功则返回0，如果有错误则返回-1

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler)
函数说明:根据参数signum指定的信号编号来设置该信号的处理函数。当指定的信号到达时就会跳转到参数handler指定的函数执行
         如果参数handler不是函数指针，则必须是下列两个常数之一:
            SIG_IGN 忽略参数signum指定的信号。
            SIG_DFL 将参数signum 指定的信号重设为核心预设的信号处理方
         在信号发生跳转到自定的handler处理函数执行后，系统会自动将此处理函数换回原来系统预设的处理方式，如果要改变此操作请改用sigaction()

int sigprocmask(int how,const sigset_t *set,sigset_t * oldset)
函数说明:改变目前的信号遮罩，其操作依参数how来决定     
        SIG_BLOCK 新的信号遮罩由目前的信号遮罩和参数set 指定的信号遮罩作联集
        SIG_UNBLOCK 将目前的信号遮罩删除掉参数set指定的信号遮罩
        SIG_SETMASK 将目前的信号遮罩设成参数set指定的信号遮罩。
        如果参数oldset不是NULL指针，那么目前的信号遮罩会由此指针返回
返回: 执行成功则返回0，如果有错误则返回-1

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
测试结果
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
同类型函数:
int sigemptyset(sigset_t *set)//将参数set信号集初始化并清空
int sigdelset(sigset_t * set,int signum)//将参数signum代表的信号从参数set信号集里删除
int sigfillset(sigset_t * set)//将参数set信号集初始化，然后把所有的信号加入到此信号集里
int sigismember(const sigset_t *set,int signum)//测试参数signum代表的信号是否已加入至参数set信号集里。
                 如果信号集里已有该信号则返回1，没有则返回0。如果有错误则返回-1
int sigpending(sigset_t *set)//将被搁置的信号集合由参数set指针返回
char * strerror(int errnum)//根据errnum的错误代码来查询其错误原因的描述字符串，然后将该字符串指针返回#include<string.h>
int pclose(FILE * stream)//关闭由popen所建立的管道及文件指针,返回子进程的结束状态。如果有错误则返回-1，错误原因存于errno中
当我们按下ctrl+c的时候，操作为：向系统发送SIGINT信号，SIGINT信号的默认处理，退出程序
当我们按下ctrl+/的时候，操作为：向系统发送SIGQUIT信号，该信号的默认处理为退出程序
***************/

