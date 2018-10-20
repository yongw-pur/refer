/*************************
头文件
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int open( const char *pathname, int flags) //int open(const char *pathname, int flags, mode_t mode)
函数说明:参数pathname文件路径字符串
参数flags
    O_RDONLY 以只读方式打开文件
    O_WRONLY 以只写方式打开文件
    O_RDWR 以可读写方式打开文件。上述三种旗标是互斥的，也就是不可同时使用，但可与下列的旗标利用OR(|)运算符组合。
    O_CREAT 若欲打开的文件不存在则自动建立该文件。
    O_EXCL 如果O_CREAT也被设置，此指令会去检查文件是否存在。文件若不存在则建立该文件，否则将导致打开文件错误。此外，若O_CREAT与O_EXCL同时设置，并且欲打开的文件为符号连接，则会打开文件失败。
    O_NOCTTY 如果欲打开的文件为终端机设备时，则不会将该终端机当成进程控制终端机。
    O_TRUNC 若文件存在并且以可写的方式打开时，此旗标会令文件长度清为0,而原来存于该文件的资料也会消失。
    O_APPEND 当读写文件时会从文件尾开始移动，也就是所写入的数据会以附加的方式加入到文件后面。
    O_NONBLOCK 以不可阻断的方式打开文件，也就是无论有无数据读取或等待，都会立即返回进程之中。
    O_NDELAY 同O_NONBLOCK。
    O_SYNC 以同步的方式打开文件,等待物理I/O结束后再write,包括更新文件属性的I/O
    O_NOFOLLOW 如果参数pathname所指的文件为一符号连接，则会令打开文件失败
    O_DIRECTORY 如果参数pathname所指的文件并非为一目录，则会令打开文件失败
参数mode
    mode参数表示设置文件访问权限的初始值，和用户掩码umask有关;0644表示-rw-r–r–
    文件权限由open的mode参数和当前进程的umask掩码共同决定
    第三个参数是在第二个参数中有O_CREAT时才作用，如果没有第三个参数可以忽略
    S_IRWXU 00700权限，代表该文件所有者具有可读、可写及可执行的权限。
    S_IRUSR 或S_IREAD，00400权限，代表该文件所有者具有可读取的权限。
    S_IWUSR 或S_IWRITE，00200 权限，代表该文件所有者具有可写入的权限。
    S_IXUSR 或S_IEXEC，00100 权限，代表该文件所有者具有可执行的权限。
    S_IRWXG 00070权限，代表该文件用户组具有可读、可写及可执行的权限。
    S_IRGRP 00040 权限，代表该文件用户组具有可读的权限。
    S_IWGRP 00020权限，代表该文件用户组具有可写入的权限。
    S_IXGRP 00010 权限，代表该文件用户组具有可执行的权限。
    S_IRWXO 00007权限，代表其他用户具有可读、可写及可执行的权限。
    S_IROTH 00004 权限，代表其他用户具有可读的权限
    S_IWOTH 00002权限，代表其他用户具有可写入的权限。
    S_IXOTH 00001 权限，代表其他用户具有可执行的权限。
返回:若所有欲核查的权限都通过了检查则返回0 值，表示成功，只要有一个权限被禁止则返回-1
    EEXIST 参数pathname 所指的文件已存在，却使用了O_CREAT和O_EXCL旗标。
    EACCESS 参数pathname所指的文件不符合所要求测试的权限。
    EROFS 欲测试写入权限的文件存在于只读文件系统内。
    EFAULT 参数pathname指针超出可存取内存空间。
    EINVAL 参数mode 不正确。
    ENAMETOOLONG 参数pathname太长。
    ENOTDIR 参数pathname不是目录。
    ENOMEM 核心内存不足。
    ELOOP 参数pathname有过多符号连接问题。
    EIO I/O 存取错误。
    使用access()作用户认证方面的判断要特别小心，例如在access()后再作open()空文件可能会造成系统安全上的问题

头文件:
#include<unistd.h>
int close(int fd)
函数说明:当使用完文件后若已不再需要则可使用close()关闭该文件，close()会让数据写回磁盘，并释放该文件所占用的资源。
         参数fd为先前由open()或creat()所返回的文件描述词
返回值:若文件顺利关闭则返回0，发生错误时返回-1;
       错误:EBADF参数fd 非有效的文件描述词或该文件已关闭

int fsync(int fd)
函数说明:fsync()负责将参数fd所指的文件数据，由系统缓冲区写回磁盘，以确保数据同步.等待写磁盘操作结束,然后返回，会影响当前线程的阻塞
返回:成功则返回0，失败返回-1，errno为错误代码

头文件:#include<stdlib.h>
int mkstemp(char * template)
函数说明:建立唯一的临时文件并打开，只有当前用户才能访问这个临时文件，并进行读、写操作
         参数template 所指的文件名称字符串中最后六个字符必须是XXXXXX
         函数会以可读写模式和0600权限来打开该文件，如果该文件不存在则会建立该文件。打开该文件后其文件描述词会返回
    返回:文件顺利打开后返回可读写的文件描述词。若果文件打开失败则返回NULL，并把错误代码存在errno 中
          EINVAL:参数template字符串最后六个字符非XXXXXX。EEXIST:无法建立临时文件
    
参数template所指的文件名称字符串必须声明为数组，如:char template[ ] ="template-XXXXXX"
不可以使用下列的表达方式char *template = "template-XXXXXX"
mkstemp函数创建的临时文件不能自动删除，执行完mkstemp函数后要调用unlink函数
unlink函数删除文件的目录入口，但临时文件还可以通过文件描述符进行访问，直到最后一个打开的进程关闭文件操作符，或者程序退出后临时文件被自动彻底地删除

头文件:
#include<stdio.h>
FILE * fopen(const char *path,const char *mode)
函数说明:参数path为文件路径及文件名
参数mode:代表着流形态
    r 打开只读文件，该文件必须存在。
    r+ 打开可读写的文件，该文件必须存在。
    w 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
    w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
    a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。
    a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。
    上述的形态字符串都可以再加一个b字符，如rb、w+b或ab＋等组合，加入b字符用来告诉函数库打开的文件为二进制文件，而非纯文字文件。
    由fopen()所建立的新文件会具有S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH(0666)权限，此文件权限也会参考umask值
返回:文件顺利打开后，指向该流的文件指针就会被返回。若果文件打开失败则返回NULL，并把错误代码存在errno

int fflush(FILE* stream)
函数说明:fflush()会强迫将缓冲区内的数据写回参数stream指定的文件中。
         如果参数stream为NULL，fflush()会将所有打开的文件数据更新
返回:成功返回0，失败返回EOF(-1)，错误代码存于errno中
     fflush(stdin)清空输入缓冲区，确保不影响后面的数据读取
     fflush()仅仅刷新位于用户空间中的流缓冲区.fflush()返回后。仅仅保证数据已不在流缓冲区中，并不保证它们一定被写到了磁盘.
     从流缓冲区刷新的数据可能已被写至磁盘。也可能还待在内核I/O缓冲区中.要确保流I/O写出的数据已写至磁盘，在调用fflush()后还应当调用fsync()
内存缓冲-----fflush---------〉内核缓冲--------fsync-----〉磁盘

**************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

main()
{
    FILE *fp;
    int fd = -1;
    
    fp = fopen("noexist","a+");
    if(fp == NULL) 
        return;
    fclose(fp);

    //如果文件存在，则清空文件内容
    fd = creat("noexist", 0); 
    printf("create file %d\n", fd);
    close(fd);

    char template[]="template-XXXXXX";
    fd = mkstemp(template);
    printf("template = %s\n",template);
    close(fd);
    unlink(template);
}


/**************
测试结果
****************/

/***************
同类型函数:
int creat(const char *pathname, mode_tmode)//创建文件，相当于open(const char *pathname , (O_CREAT|O_WRONLY|O_TRUNC), mode);
int fclose(FILE * stream) //关闭文件流
int fdatasync(int fd) //只影响文件的数据部分,fsync还会同步更新文件属性
int sync(void) //sync函数只是将所有修改过的块缓冲区排入写队列，然后就返回，它并不等待实际写磁盘操作结束
char * mktemp(char * template)//产生唯一的临时文件名，参数template所指的文件名称字符串中最后六个字符必须是XXXXXX。产生后的文件名会借字符串指针返回
FILE *tmpfile(void)//以wb+形式创建唯一一个临时二进制文件，并打开文件。
                    The file will be automatically deleted when it is closed or the program terminates.
FILE * freopen(const char * path,const char * mode,FILE * stream)// 将原stream所打开的文件流关闭，然后打开参数path的文件
                   参数path文件路径及文件名，mode参考fopen(),参数stream为已打开的文件指针
                   freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取

***************/

