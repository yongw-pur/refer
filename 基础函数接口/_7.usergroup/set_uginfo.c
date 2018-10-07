/*************************
ͷ�ļ�
#include<unistd.h>
#include<sys/types.h>
gid_t getegid(void);
����˵��:��ȡִ��Ŀǰ������Ч��ʶ���롣��Ч����ʶ����������������ִ��ʱ���Ȩ��
         returns the effective group ID of the calling process.(Ȩ���е�Sλ-->sudoȨ��)
����:��Ч����ʶ����

uid_t geteuid(void)
����˵��:��ȡִ��Ŀǰ������Ч���û�ʶ���룬��Ч���û�ʶ����������������ִ�е�Ȩ��
         ���ɴ˸ı��ֵ�����̿��Ի�ö����Ȩ�ޡ�
         ����ִ���ļ���setIDλ�ѱ����ã����ļ�ִ��ʱ������̵�euidֵ�����ɸ��ļ������ߵ�uid
         ���磬ִ���ļ�/usr/bin/passwd��Ȩ��Ϊ-r-s--x--x����s λ��ΪsetID(SUID)λ
         �����κ��û���ִ��passwd ʱ����Ч���û�ʶ����ᱻ���passwd �����ߵ�uid ֵ����root��uid ֵ(0)

ͷ�ļ�
#include<utmp.h>
void pututline(struct utmp *ut)
����˵��:������ut��utmp�ṹ��¼��utmp�ļ��С�
         �˺���������getutid()��ȡ����ȷ��д��λ��
         ���û���ҵ�����ļ�¼�����뵽utmp�ļ�β

ͷ�ļ�
#include<unistd.h>
int setuid(uid_t uid)
����˵��:��������ִ��Ŀǰ���̵��û�ʶ���롣
         Ҫ�ô˺��������ã�����Ч���û�ʶ�������Ϊ0(root)��
         ��Linux�£���rootʹ��setuid()���任�������û�ʶ����ʱ��rootȨ�޻ᱻ��������ȫת���ɸ��û���ݣ�
         Ҳ����˵���ý������󽫲��پ��п�setuid()��Ȩ�������ֻ������ʱ����root Ȩ�ޣ��Ժ�������ȡ��Ȩ�ޣ������ʹ��seteuid()
����ֵ:ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno

ͷ�ļ�
#include<grp.h>
#include<sys/types.h>
void setgrent(void)
����˵��:����getgrent()�Ķ�д��ַָ�����ļ���ͷ�����¶�ȡ

ͷ�ļ�
#include<utmp.h>
void utmpname(const char * file)
����˵��:����utmp�ļ���·�������ṩutmp��غ����Ĵ�ȡ·�������û��ʹ��utmpname()��Ĭ��utmp�ļ�·��Ϊ/var/run/utmp

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
���Խ��
****************/

/***************
ͬ���ͺ���:
gid_t getgid(void)ȡ��ִ��Ŀǰ���̵���ʶ����;returns the real group ID of the calling process.
        ����:gid is 0 //��ʹ��root���ִ�з�������ʱ
uid_t getuid(void)ȡ��ִ��Ŀǰ���̵��û�ʶ����
int seteuid(uid_t euid)��������ִ��Ŀǰ���̵���Ч�û�ʶ���롣��Linux�£�seteuid(euid)�൱��setreuid(-1,euid)
int setfsgid(uid_t fsgid)������������Ŀǰ���̵��ļ�ϵͳ����ʶ���롣һ������£��ļ�ϵͳ����ʶ����(fsgid)����Ч����ʶ����(egid)����ͬ�ġ�����ǳ����û����ô˺���������fsgid ����Ϊ�κ�ֵ���������fsgid����Ϊreal/effective/saved����ʶ����֮һ
int setfsuid(uid_t fsuid)������������Ŀǰ���̵��ļ�ϵͳ���û�ʶ���롣һ������£��ļ�ϵͳ���û�ʶ����(fsuid)����Ч���û�ʶ����(euid)����ͬ�ġ�����ǳ����û����ô˺���������fsuid����Ϊ�κ�ֵ���������fsuid����Ϊreal/effective/saved���û�ʶ����֮һ
int setgid(gid_t gid)��Ŀǰ���̵���ʵ��ʶ����(real gid)��ɲ���gidֵ��������Գ����û����ִ�д˵��ã���real��effective��savedgid������ɲ���gid
void setpwent(void)������getpwent()�Ķ�д��ַָ�������ļ���ͷ
void setutent(void)��getutent()�Ķ�д��ַָ��utmp�ļ���ͷ
***************/

