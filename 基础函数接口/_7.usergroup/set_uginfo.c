/*************************
头文件
#include<unistd.h>
#include<sys/types.h>
gid_t getegid(void);
函数说明:获取执行目前进程有效组识别码。有效的组识别码用来决定进程执行时组的权限
         returns the effective group ID of the calling process.(权限中的S位-->sudo权限)
返回:有效的组识别码

uid_t geteuid(void)
函数说明:获取执行目前进程有效的用户识别码，有效的用户识别码用来决定进程执行的权限
         借由此改变此值，进程可以获得额外的权限。
         倘若执行文件的setID位已被设置，该文件执行时，其进程的euid值便会设成该文件所有者的uid
         例如，执行文件/usr/bin/passwd的权限为-r-s--x--x，其s 位即为setID(SUID)位
         而当任何用户在执行passwd 时其有效的用户识别码会被设成passwd 所有者的uid 值，即root的uid 值(0)

头文件
#include<utmp.h>
void pututline(struct utmp *ut)
函数说明:将参数ut的utmp结构记录到utmp文件中。
         此函数会先用getutid()来取得正确的写入位置
         如果没有找到相符的记录则会加入到utmp文件尾

头文件
#include<unistd.h>
int setuid(uid_t uid)
函数说明:重新设置执行目前进程的用户识别码。
         要让此函数有作用，其有效的用户识别码必须为0(root)。
         在Linux下，当root使用setuid()来变换成其他用户识别码时，root权限会被抛弃，完全转换成该用户身份，
         也就是说，该进程往后将不再具有可setuid()的权利，如果只是向暂时抛弃root 权限，稍后想重新取回权限，则必须使用seteuid()
返回值:执行成功则返回0，失败则返回-1，错误代码存于errno

头文件
#include<grp.h>
#include<sys/types.h>
void setgrent(void)
函数说明:来将getgrent()的读写地址指回组文件开头，重新读取

头文件
#include<utmp.h>
void utmpname(const char * file)
函数说明:设置utmp文件的路径，以提供utmp相关函数的存取路径。如果没有使用utmpname()则默认utmp文件路径为/var/run/utmp

**************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

main()
{
    printf("egid is %d\n",getegid());
    printf ("euid is %d \n",geteuid());
}


/**************
测试结果
****************/

/***************
同类型函数:
gid_t getgid(void)取得执行目前进程的组识别码;returns the real group ID of the calling process.
        例如:gid is 0 //当使用root身份执行范例程序时
uid_t getuid(void)取得执行目前进程的用户识别码
int seteuid(uid_t euid)重新设置执行目前进程的有效用户识别码。在Linux下，seteuid(euid)相当于setreuid(-1,euid)
int setfsgid(uid_t fsgid)用来重新设置目前进程的文件系统的组识别码。一般情况下，文件系统的组识别码(fsgid)与有效的组识别码(egid)是相同的。如果是超级用户调用此函数，参数fsgid 可以为任何值，否则参数fsgid必须为real/effective/saved的组识别码之一
int setfsuid(uid_t fsuid)用来重新设置目前进程的文件系统的用户识别码。一般情况下，文件系统的用户识别码(fsuid)与有效的用户识别码(euid)是相同的。如果是超级用户调用此函数，参数fsuid可以为任何值，否则参数fsuid必须为real/effective/saved的用户识别码之一
int setgid(gid_t gid)将目前进程的真实组识别码(real gid)设成参数gid值。如果是以超级用户身份执行此调用，则real、effective与savedgid都会设成参数gid
void setpwent(void)用来将getpwent()的读写地址指回密码文件开头
void setutent(void)将getutent()的读写地址指回utmp文件开头
***************/

