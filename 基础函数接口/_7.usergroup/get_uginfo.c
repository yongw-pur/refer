/*************************
ͷ�ļ�
#include<grp.h>
#include <sys/types.h>
struct group *getgrent(void);
����˵��:�����ļ�(/etc/group)�ж�ȡһ�������ݣ���������group�ṹ���ء�
         ��һ�ε���ʱ��ȡ�õ�һ��������(������ļ�����ȡ������Ϻ�ʹ��endgrent()���رո����ļ�)
         ֮��ÿ����һ�ξͻ᷵����һ�����ݣ�ֱ�������κ�����ʱ����NULL��
����:group�ṹ���ݣ��������NULL���ʾ�������ݻ��д�����
struct group{
    char *gr_name; //������
    char *gr_passwd; //������
    gid_t gr_gid; //��ʶ����
    char **gr_mem; //���Ա�˺�
}

struct group * fgetgrent(FILE * stream);
����˵��:�Ӳ���streamָ�����ļ���ȡһ�����ݣ�Ȼ����group�ṹ�������ݷ��ء�
         ����stream��ָ�����ļ����etc/group��ͬ�ĸ�ʽ

ͷ�ļ�
#include<pwd.h>
#include <sys/types.h>
strcut passwd * getpwent(void);
����˵��:�����������ļ���/etc/passwd���ж�ȡһ���û����ݣ����û���������passwd�ṹ���ء�
         ��һ�ε���ʱ��ȡ�õ�һλ�û�����(��������ļ�����ȡ������Ϻ�ʹ��endpwent()�رո������ļ�)
         ֮��ÿ����һ�ξͻ᷵����һ�����ݣ�ֱ�������κ�����ʱ����NULL
����:passwd �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�����
struct passwd{
    char * pw_name; //�û��˺�
    char * pw_passwd; //�û�����
    uid_t pw_uid; //�û�ʶ����
    gid_t pw_gid; //��ʶ����
    char * pw_gecos; //�û�ȫ��
    char * pw_dir; //��Ŀ¼
    char * pw_shell; //��ʹ�õ�shell·��
};

struct passwd * fgetpwent(FILE *stream);
����˵��:�Ӳ���streamָ�����ļ���ȡһ�����ݣ�Ȼ����passwd�ṹ�������ݷ��ء�
         ����stream��ָ�����ļ������/etc/passwd��ͬ�ĸ�ʽ

ͷ�ļ�
#include<utmp.h>
struct utmp *getutent(void);
����˵��:��utmp �ļ�(/var/run/utmp)�ж�ȡһ���¼���ݣ���������utmp �ṹ���ء�
         ��һ�ε���ʱ��ȡ�õ�һλ�û����ݣ�֮��ÿ����һ�ξͻ᷵����һ������
         ֱ�������κ�����ʱ����NULL,ʹ��endutent()�ر�
struct utmp
{
    short int ut_type; //��¼����
    pid_t ut_pid; //login���̵�pid
    char ut_line[UT_LINESIZE];//��¼װ������ʡ����"/dev/"
    char ut_id[4]; //Inittab ID
    char ut_user[UT_NAMESIZE];//��¼�˺�
    char ut_host[UT_HOSTSIZE];//��¼�˺ŵ�Զ����������
    struxt exit_status ut_exit;//������ΪDEAD_PROCESSʱ���̵Ľ���״̬
    long int ut_session; //Sessioc ID
    struct timeval ut_tv; //ʱ���¼
    int32_t ut_addr_v6[4]; //Զ�������������ַ
    char __unused[20]; //����δʹ��
};
exit_status�ṹ����
struct exit_status
{
    short int e_termination; //���̽���״̬
    short int e_exit; //�����˳�״̬
};
ut_type�����¼�������:
EMPTY ��Ϊ�յļ�¼��
RUN_LVL ��¼ϵͳrun��level�ĸı�
BOOT_TIME ��¼ϵͳ����ʱ��
NEW_TIME ��¼ϵͳʱ��ı���ʱ��
OLD_TINE ��¼���ı�ϵͳʱ��ʱ��ʱ�䡣
INIT_PROCESS ��¼һ����init���������Ľ��̡�
LOGIN_PROCESS ��¼login���̡�
USER_PROCESS ��¼һ����̡�
DEAD_PROCESS ��¼һ�����Ľ��̡�
ACCOUNTING Ŀǰ��δʹ��
��س�����������:
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
���Խ��
****************/

/***************
ͬ���ͺ���:
strcut group * getgrgid(gid_t gid)������gidָ������ʶ������һ�������ļ����ҵ�ʱ�㽫�����������group�ṹ����
strcut group * getgrnam(const char * name)��һ����������ôָ���������ƣ��ҵ�ʱ�㽫�����������group�ṹ����
int getpw(uid_t uid,char *buf)��/etc/passwd�в��ҷ��ϲ���uid��ָ�����û��˺����ݣ��Ҳ���������ݾͷ���-1
                    �����ص�buf�ַ�����ʽ����:�˺�:����:�û�ʶ����(uid):��ʶ����(gid):ȫ��:��Ŀ¼:shell
                    ע��:getpw()����Ǳ�ڵİ�ȫ�����⣬�뾡��ʹ�ñ�ĺ���ȡ����
                    ʹ��shadow��ϵͳ�Ѱ��û�������/etc/passwd�����ʹ��getpw()ȡ�õ����뽫Ϊ"x"
struct passwd * getpwnam(const char * name)��һ��������nameָ�����˺�����
                    �ҵ�ʱ�㽫���û���������passwd�ṹ����,NULL���ʾδ�ҵ�(��nameΪ�ؼ��ֲ���)
struct passwd * getpwuid(uid_t uid)��һ��������uid ָ�����û�ʶ����
                    �ҵ�ʱ�㽫���û���������passwd�ṹ����,NULL���ʾδ�ҵ�(��uidΪ�ؼ��ֲ���)
strcut utmp *getutid(strcut utmp *ut)��Ŀǰutmp �ļ��Ķ�дλ����һ������������utָ���ļ�¼
                    ���ut->ut_typeΪRUN_LVL��BOOT_TIME��NEW_TIME��OLD_TIME����֮һ�������ut->ut_type ����ļ�¼
                    ��ut->ut_type ΪINIT_PROCESS��LOGIN_PROCESS��USER_PROCESS��DEAD_PROCESS����֮һ���������ut->ut_id����ļ�¼
                    �ҵ�����ļ�¼�㽫��������utmp �ṹ����
struct utmp *getutline (struct utmp *ut)utmp�ļ��Ķ�дλ����һ��������ut_typeΪUSER_PROCESS ��LOGIN_PROCESS�ļ�¼
                    ����ut_line ��ut->ut_line ������ҵ�����ļ�¼�㽫��������utmp�ṹ����
***************/

