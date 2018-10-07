/*************************
头文件
#include<grp.h>
#include <sys/types.h>
struct group *getgrent(void);
函数说明:从组文件(/etc/group)中读取一项组数据，该数据以group结构返回。
         第一次调用时会取得第一项组数据(会打开组文件，读取数据完毕后使用endgrent()来关闭该组文件)
         之后每调用一次就会返回下一项数据，直到已无任何数据时返回NULL。
返回:group结构数据，如果返回NULL则表示已无数据或有错误发生
struct group{
    char *gr_name; //组名称
    char *gr_passwd; //组密码
    gid_t gr_gid; //组识别码
    char **gr_mem; //组成员账号
}

struct group * fgetgrent(FILE * stream);
函数说明:从参数stream指定的文件读取一行数据，然后以group结构将该数据返回。
         参数stream所指定的文件须和etc/group相同的格式

头文件
#include<pwd.h>
#include <sys/types.h>
strcut passwd * getpwent(void);
函数说明:用来从密码文件（/etc/passwd）中读取一项用户数据，该用户的数据以passwd结构返回。
         第一次调用时会取得第一位用户数据(会打开密码文件，读取数据完毕后使用endpwent()关闭该密码文件)
         之后每调用一次就会返回下一项数据，直到已无任何数据时返回NULL
返回:passwd 结构数据，如果返回NULL 则表示已无数据，或有错误发生
struct passwd{
    char * pw_name; //用户账号
    char * pw_passwd; //用户密码
    uid_t pw_uid; //用户识别码
    gid_t pw_gid; //组识别码
    char * pw_gecos; //用户全名
    char * pw_dir; //家目录
    char * pw_shell; //所使用的shell路径
};

struct passwd * fgetpwent(FILE *stream);
函数说明:从参数stream指定的文件读取一行数据，然后以passwd结构将该数据返回。
         参数stream所指定的文件必须和/etc/passwd相同的格式

头文件
#include<utmp.h>
struct utmp *getutent(void);
函数说明:从utmp 文件(/var/run/utmp)中读取一项登录数据，该数据以utmp 结构返回。
         第一次调用时会取得第一位用户数据，之后每调用一次就会返回下一项数据
         直到已无任何数据时返回NULL,使用endutent()关闭
struct utmp
{
    short int ut_type; //登录类型
    pid_t ut_pid; //login进程的pid
    char ut_line[UT_LINESIZE];//登录装置名，省略了"/dev/"
    char ut_id[4]; //Inittab ID
    char ut_user[UT_NAMESIZE];//登录账号
    char ut_host[UT_HOSTSIZE];//登录账号的远程主机名称
    struxt exit_status ut_exit;//当类型为DEAD_PROCESS时进程的结束状态
    long int ut_session; //Sessioc ID
    struct timeval ut_tv; //时间记录
    int32_t ut_addr_v6[4]; //远程主机的网络地址
    char __unused[20]; //保留未使用
};
exit_status结构定义
struct exit_status
{
    short int e_termination; //进程结束状态
    short int e_exit; //进程退出状态
};
ut_type有以下几种类型:
EMPTY 此为空的记录。
RUN_LVL 记录系统run－level的改变
BOOT_TIME 记录系统开机时间
NEW_TIME 记录系统时间改变后的时间
OLD_TINE 记录当改变系统时间时的时间。
INIT_PROCESS 记录一个由init衍生出来的进程。
LOGIN_PROCESS 记录login进程。
USER_PROCESS 记录一般进程。
DEAD_PROCESS 记录一结束的进程。
ACCOUNTING 目前尚未使用
相关常数定义如下:
UT_LINESIZE 32
UT_NAMESIZE 32
UT_HOSTSIZE 256

**************************/
#include<grp.h>
#include<stdio.h>
#include<sys/types.h>
main()
{
    //get /etc/group data
    int i;
    struct group *data;
#ifdef FGRENT
    FILE *stream;
    stream = fopen("/etc/group", "r");
    while((data= fgetgrent(stream)) != NULL)
#else
    while((data= getgrent()) != NULL)
#endif
    {
        i=0;
        printf("%s:%s:%d:",data->gr_name,data->gr_passwd,data->gr_gid);
        while(data->gr_mem[i])
            printf("%s,",data->gr_mem[i++]);
        printf("\n");
    }
#ifdef FGRENT
    fclose(stream);
#else
    endgrent();
#endif

}


/**************
测试结果
****************/

/***************
同类型函数:
strcut group * getgrgid(gid_t gid)依参数gid指定的组识别码逐一搜索组文件，找到时便将该组的数据以group结构返回
strcut group * getgrnam(const char * name)逐一搜索参数那么指定的组名称，找到时便将该组的数据以group结构返回
int getpw(uid_t uid,char *buf)从/etc/passwd中查找符合参数uid所指定的用户账号数据，找不到相关数据就返回-1
                    所返回的buf字符串格式如下:账号:密码:用户识别码(uid):组识别码(gid):全名:根目录:shell
                    注意:getpw()会有潜在的安全性问题，请尽量使用别的函数取代。
                    使用shadow的系统已把用户密码抽出/etc/passwd，因此使用getpw()取得的密码将为"x"
struct passwd * getpwnam(const char * name)逐一搜索参数name指定的账号名称
                    找到时便将该用户的数据以passwd结构返回,NULL则表示未找到(以name为关键字查找)
struct passwd * getpwuid(uid_t uid)逐一搜索参数uid 指定的用户识别码
                    找到时便将该用户的数据以passwd结构返回,NULL则表示未找到(以uid为关键字查找)
strcut utmp *getutid(strcut utmp *ut)从目前utmp 文件的读写位置逐一往后搜索参数ut指定的记录
                    如果ut->ut_type为RUN_LVL，BOOT_TIME，NEW_TIME，OLD_TIME其中之一则查找与ut->ut_type 相符的记录
                    若ut->ut_type 为INIT_PROCESS，LOGIN_PROCESS，USER_PROCESS或DEAD_PROCESS其中之一，则查找与ut->ut_id相符的记录
                    找到相符的记录便将该数据以utmp 结构返回
struct utmp *getutline (struct utmp *ut)utmp文件的读写位置逐一往后搜索ut_type为USER_PROCESS 或LOGIN_PROCESS的记录
                    而且ut_line 和ut->ut_line 相符。找到相符的记录便将该数据以utmp结构返回
***************/

