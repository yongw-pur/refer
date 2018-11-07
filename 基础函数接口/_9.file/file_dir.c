/*************************
头文件
#include<unistd.h>
int access(const char *pathname,int mode)
函数说明:检查是否可以读/写某一已存在的文件
        参数mode:R_OK(4)，W_OK(2)与X_OK(1)用来检查文件是否具有读取、写入和执行的权限
                 F_OK(0)则是用来判断该文件是否存在
返回:权限都通过了检查则返回0值;只要有一权限被禁止则返回-1
    EACCESS 参数pathname所指定的文件不符合所要求测试的权限
    EROFS 欲测试写入权限的文件存在于只读文件系统内
    EFAULT 参数pathname指针超出可存取内存空间
    EINVAL 参数mode不正确
    ENAMETOOLONG 参数pathname太长
    ENOTDIR 参数pathname为一目录
    ENOMEM 核心内存不足
    ELOOP 参数pathname有过多符号连接问题
    EIO I/O存取错误

char * getcwd(char * buf,size_t size)
函数说明:将当前的工作目录绝对路径复制到参数buf所指的内存空间，参数size为buf的空间大小
         若参数buf为NULL，getcwd()会依参数size的大小自动配置内存(使用malloc())，如果参数size也为0，则getcwd()会依工作目录绝对路径的字符串程度来决定所配置的内存大小
返回:执行成功则将结果复制到参数buf所指的内存空间，或是返回自动配置的字符串指针。失败返回NULL

int ftruncate(int fd,off_t length)
函数说明:将参数fd指定的文件大小改为参数length指定的大小;如果原来的文件大小比参数length大，则超过的部分会被删去
返回:执行成功则返回0，失败返回-1 
    EBADF 参数fd文件描述词为无效的或该文件已关闭。
    EINVAL 参数fd 为一socket 并非文件，或是该文件并非以写入模式打开
    需要重新设置文件读写位置: lseek(fd,0,SEEK_SET);或者rewind

int link (const char *oldpath,const char *newpath)
函数说明:以参数newpath指定的名称来建立一个新的连接(硬连接)到参数oldpath所指定的已存在文件。如果参数newpath指定的名称为一已存在的文件则不会建立连接
返回:成功则返回0，失败返回-1,link()所建立的硬连接无法跨越不同文件系统，如果需要请改用symlink

头文件
#include<sys/stat.h>
#include<unistd.h>
int stat(const char *file_name,struct stat *buf)
函数说明:获取文件状态，复制到参数buf所指的结构中
         stat结构参数:
            struct stat
            {
                dev_t st_dev; //文件设备编号
                ino_t st_ino; //inode
                mode_t st_mode; //文件的类型和存取的权限
                nlink_t st_nlink; //连到该文件的硬连接数目，刚建立的文件值为1
                uid_t st_uid; //文件所有者的用户识别码
                gid_t st_gid; //文件所有者的组识别码
                dev_t st_rdev; //若此文件为装置设备文件，则为其设备编号
                off_t st_size; //total size, in bytes
                unsigned long st_blksize; //文件系统的I/O缓冲区大小
                unsigned long st_blocks; //占用文件区块的个数，每一区块大小为512 个字节
                time_t st_atime; //time of lastaccess:mknod、utime、read、write与tructate时改变
                time_t st_mtime; //time of last modification:mknod、utime和write时才会改变
                time_t st_ctime; //time of last change:参数会在文件所有者、组、权限被更改时更新
            };
返回:执行成功则返回0，失败返回-1

int chmod(const char *path,mode_t mode)
函数说明:依参数mode 权限来更改参数path 指定文件的权限
         参数mode:
            S_ISUID 04000 文件的（set user-id on execution）位
            S_ISGID 02000 文件的（set group-id on execution）位
            S_ISVTX 01000 文件的sticky位
            S_IRUSR（S_IREAD） 00400 文件所有者具可读取权限
            S_IWUSR（S_IWRITE）00200 文件所有者具可写入权限
            S_IXUSR（S_IEXEC） 00100 文件所有者具可执行权限
            S_IRGRP 00040 用户组具可读取权限
            S_IWGRP 00020 用户组具可写入权限
            S_IXGRP 00010 用户组具可执行权限
            S_IROTH 00004 其他用户具可读取权限
            S_IWOTH 00002 其他用户具可写入权限
            S_IXOTH 00001 其他用户具可执行权限
返回:权限改变成功返回0，失败返回-1

头文件
#include<dirent.h>
int alphasort(const struct dirent **a,const struct dirent **b)
函数说明:依字母顺序排序目录结构;scandir最后调用qsort函数时作为判断的函数
dirent.d_type:DT_UNKNOWN = 0, DT_FIFO = 1, DT_CHR = 2, DT_DIR = 4,
              DT_BLK = 6, DT_REG = 8,DT_LNK = 10, DT_SOCK = 12

DIR *opendir(const char * name)
函数说明:打开参数name指定的目录，并返回DIR*形态的目录流,接下来对目录的读取和搜索都要使用此返回值
返回:成功则返回DIR* 型态的目录流，打开失败则返回NULL

struct dirent * readdir(DIR * dir)
函数说明:读取目录
返回:参数dir目录流的下个目录进入点
        struct dirent
        {
            __ino_t d_ino; //此目录进入点的inode
            __off_t d_off; //目录文件开头至此目录进入点的位移
            unsigned short int d_reclen;//_name的长度，不包含NULL字符
            unsigned char d_type;//文件类型
            char d_name[256];//文件名
        };

int readlink(const char *path ,char *buf,size_t bufsiz)
函数说明:取得符号连接所指的文件路径,保存到到参数buf所指的内存空间
返回:字符串的字符数返回(需要人为加上\0)若参数bufsiz小于符号连接的内容长度，过长的内容会被截断

int rename(const char *oldpath, const char *newpath)
函数说明:将参数oldpath所指定的文件名称改为参数newpath所指的文件名称。若newpath所指定的文件已存在，oldpath则会被删除
返回:执行成功则返回0，失败返回-1 (相当于mv命令，old移动到new，使用new名字，内容为old内容)

int remove(const char *pathname)
函数说明:删除参数pathname指定的文件。如果参数pathname为一文件，则调用unlink()处理，若参数pathname为一目录，则调用rmdir来处理

int unlink(const char *pathname)
函数说明:删除参数pathname指定的文件。如果该文件名为最后连接点，但有其他进程打开了此文件，则在所有关于此文件的文件描述词皆关闭后才会删除。
         如果参数pathname为一符号连接，则此连接会被删除
返回:成功则返回0，失败返回-1

头文件
#include<sys/types.h>
#include<utime.h>
int utime(const char *filename,struct utimbuf *buf)
函数说明:修改参数filename文件所属的inode存取时间;参数buf为空指针(NULL)，则该文件的存取时间和更改时间全部会设为目前时间
     参数buf:
        struct utimbuf{
            time_t actime;
            time_t modtime;
        };
        
**************************/
#include<dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<utime.h>


int Filter(const struct dirent *pDir)
{
    if (pDir->d_type & 0x04 
        && strcmp(pDir->d_name, ".")
        && strcmp(pDir->d_name, ".."))
    {
        return 1;
    }
    return 0;
}

void main()
{
    if (access("/etc/passwd",R_OK) == 0)
        printf("/etc/passwd can be read\n");

    int i,total;
    struct dirent **namelist;
    total = scandir("/", &namelist, Filter, alphasort); //int (*filter)(const void *b)
    if(total <0)
        perror("scandir");
    else
    {
        for(i=0;i<total;i++)
        {
            printf("%s\n",namelist[i]->d_name);
        }
        printf("total = %d\n",total);
    }

    
    int fd;
    fd = open("/etc", O_RDONLY);
    fchdir(fd); //需要为路径才能切换
    printf("current working directory : %s \n",getcwd(NULL,NULL));
    close(fd);

    DIR *dir;
    struct dirent *ptr;
    dir = opendir("/etc");
    if(dir == NULL)
    {
        printf("opendir fail\n");
        return;
    }
    
    while((ptr = readdir(dir))!=NULL)
    {
        //包括文件和目录
        printf("d_name: %s\n",ptr->d_name);
    }
    closedir(dir);
}


/**************
测试结果
****************/

/***************
同类型函数:
int chdir(const char *path)//将当前的工作目录改变成以参数path所指的目录
int chroot(const char *path)//改变根目录为参数path 所指定的目录。只有超级用户才允许改变根目录，子进程将继承新的根目录
int chown(const char *path, uid_t owner,gid_t group)//指定文件的所有者变更为owner代表的用户,文件的组变更为group组
int fchmod(int fildes,mode_t mode)//更改参数fildes所指文件的权限,参数mode请参考chmod
int fchown(int fd,uid_t owner,gid_t group)//指定文件的所有者变更为owner代表的用户,文件的组变更为group组
int fstat(int fildes,struct stat *buf)//将参数fildes所指的文件状态，复制到参数buf所指的结构中(struct stat)
                  fstat与stat作用完全相同，不同处在于传入的参数为已打开的文件描述词
int fchdir(int fd)//当前的工作目录改变成以参数fd 所指的文件描述词
int lstat (const char *file_name.struct stat *buf)//取得参数file_name所指的文件状态,当文件为符号连接时,lstat会返回该link本身的状态
int symlink( const char *oldpath,const char *newpath)//以参数newpath指定的名称来建立一个新的连接(符号连接)到参数oldpath所指定的已存在文件
int truncate(const char *path,off_t length)//将参数path 指定的文件大小改为参数length 指定的大小。如果原来的文件大小比参数length大，则超过的部分会被删去
void rewinddir(DIR *dir)//设置参数dir 目录流目前的读取位置为原来开头的读取位置，readdir
void seekdir(DIR *dir,off_t offset)//设置参数dir目录流目前的读取位置，在调用readdir()时便从此新位置开始读取
off_t telldir(DIR *dir)//返回参数dir目录流目前的读取位置。此返回值代表距离目录文件开头的偏移量，返回值返回下个读取位置
int rmdir( const char *dirname )//删除一个目录，若成功则返回0，否则返回-1,删除文件返回-1
int utimes(char * filename.struct timeval *tvp)//修改参数filename文件所属的inode存取时间和修改时间
               tvp[0].tc_sec则为utimbuf.actime，tvp]1].tv_sec 为utimbuf.modtime
***************/

