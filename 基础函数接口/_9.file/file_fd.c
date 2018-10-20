/*************************
头文件
#include<unistd.h>
int dup (int oldfd)
函数说明:复制参数oldfd所指的文件描述词，并将它返回。
         新的文件描述词和oldfd指向同一个文件，共享所有的锁定、读写位置和各项权限或旗标。但文件描述词之间并不共享close-on-exec旗标
         例如，当利用lseek()对某个文件描述词作用时，另一个文件描述词的读写位置也会随着改变。
返回:当复制成功时，则返回最小及尚未使用的文件描述词。
     若有错误则返回-1，errno会存放错误代码。错误代码EBADF参数fd非有效的文件描述词，或该文件已关闭
close(1);
fd2=dup(fd1); //返回的一定是1，因为刚关闭标准输出，则输出的内容不会在命令行显示，输出的内容显示在1.txt中，1.txt文件和标准输出就绑定起来了，所以以后输出到标准输出的信息就可以到1.txt中查看
想像标准输入输出就是打开的文件,读写的内容都是用户控制，控制写到的地方在哪儿. fd 0 1 2 分别表示 标准输入，标准输出，标准错误。后两个是输出

头文件
#include<unistd.h>
#include<fcntl.h>
int fcntl(int fd, int cmd, ...)//int fcntl(int fd,int cmd,long arg) int fcntl(int fd,int cmd,struct flock * lock)
函数说明:操作文件描述符的特性
         参数cmd:
            F_DUPFD：复制文件描述符
            F_DUPFD_CLOEXEC：复制文件描述符，新文件描述符被设置了close-on-exec
            F_GETFD：读取文件描述标识
            F_SETFD 设置close-on-exec 旗标。该旗标以参数arg的FD_CLOEXEC位决定。
            F_GETFL 取得文件描述词状态旗标，此旗标为open的参数flags。
            F_SETFL 设置文件描述词状态旗标，参数arg为新旗标，但只允许O_APPEND、O_NONBLOCK和O_ASYNC位的改变，其他位的改变将不受影响。
            F_GETLK 取得文件锁定的状态。
            F_SETLK 设置文件锁定的状态。此时flcok结构的l_type 值必须是F_RDLCK、F_WRLCK或F_UNLCK。如果无法建立锁定，则返回-1，错误代码为EACCES 或EAGAIN。
            F_SETLKW F_SETLK 作用相同，但是无法建立锁定时，此调用会一直等到锁定动作成功为止。若在等待锁定的过程中被信号中断时，会立即返回-1，错误代码为EINTR
         参数lock指针为flock 结构指针
            struct flcok
            {
                short int l_type; //锁定的状态 F_RDLCK 建立一个供读取用的锁定; F_WRLCK 建立一个供写入用的锁定; F_UNLCK 删除之前建立的锁定
                short int l_whence;//决定l_start位置 SEEK_SET 以文件开头为锁定的起始位置; SEEK_CUR 以目前文件读写位置为锁定的起始位置 SEEK_END 以文件结尾为锁定的起始位置
                off_t l_start; //锁定区域的开头位置
                off_t l_len; //锁定区域的大小
                pid_t l_pid; //锁定动作的进程
            };
返回:get操作成功返回flag,arg设置为0

头文件
#include<sys/file.h>
int flock(int fd,int operation)
函数说明:flock()按照operation指定方式对参数fd所指的文件做锁定或解除锁定的动作。
         此函数只能锁定整个文件，无法锁定文件的某一区域
         参数operation
            LOCK_SH 建立共享锁定。多个进程可同时对同一个文件作共享锁定，判断是没有加锁的0(读锁)
            LOCK_EX 建立互斥锁定。一个文件同时只有一个互斥锁定 (0 == flock(fd, LOCK_EX)能获取锁)(写锁)
            LOCK_UN 解除文件锁定状态。
            LOCK_NB 无法建立锁定时，此操作可不被阻断，马上返回进程。通常与LOCK_SH或LOCK_EX 做(|)组合
            i = flock(fd, LOCK_SH | LOCK_NB)判断是否加锁，使用dup()或fork()时文件描述词不会继承此种锁定。在加了读锁的情况下，加写锁是不成功的
返回:0表示成功，若有错误则返回-1，错误代码存于errno

头文件
#include<stdio.h>
FILE * fdopen(int fildes,const char * mode)
函数说明:将参数fildes的文件描述词(fd)，转换为对应的文件指针后返回
         mode 字符串则代表着文件指针的流形态，此形态必须和原先文件描述词读写模式相同(参考fopen)


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
    /*检查锁的状态
    int i = flock(fileno(f), LOCK_EX | LOCK_NB);
    printf("i %d\n", i);*/

    FILE *fp = fdopen(0,"w+");
    fprintf(fp,"%s\n", "hello!");
    fclose(fp);
}


/**************
测试结果
****************/

/***************
同类型函数:
int dup2(int odlfd,int newfd)//复制参数oldfd所指的文件描述词，并将它拷贝至参数newfd后一块返回。若参数newfd为一已打开的文件描述词，则newfd所指的文件会先被关闭
                             dup2()相当于调用fcntl(oldfd，F_DUPFD，newfd),返回和dup相同
int fileno(FILE * stream) //获得参数stream指定的文件流所使用的文件描述符
***************/

