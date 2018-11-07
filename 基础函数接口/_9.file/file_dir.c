/*************************
ͷ�ļ�
#include<unistd.h>
int access(const char *pathname,int mode)
����˵��:����Ƿ���Զ�/дĳһ�Ѵ��ڵ��ļ�
        ����mode:R_OK(4)��W_OK(2)��X_OK(1)��������ļ��Ƿ���ж�ȡ��д���ִ�е�Ȩ��
                 F_OK(0)���������жϸ��ļ��Ƿ����
����:Ȩ�޶�ͨ���˼���򷵻�0ֵ;ֻҪ��һȨ�ޱ���ֹ�򷵻�-1
    EACCESS ����pathname��ָ�����ļ���������Ҫ����Ե�Ȩ��
    EROFS ������д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ��
    EFAULT ����pathnameָ�볬���ɴ�ȡ�ڴ�ռ�
    EINVAL ����mode����ȷ
    ENAMETOOLONG ����pathname̫��
    ENOTDIR ����pathnameΪһĿ¼
    ENOMEM �����ڴ治��
    ELOOP ����pathname�й��������������
    EIO I/O��ȡ����

char * getcwd(char * buf,size_t size)
����˵��:����ǰ�Ĺ���Ŀ¼����·�����Ƶ�����buf��ָ���ڴ�ռ䣬����sizeΪbuf�Ŀռ��С
         ������bufΪNULL��getcwd()��������size�Ĵ�С�Զ������ڴ�(ʹ��malloc())���������sizeҲΪ0����getcwd()��������Ŀ¼����·�����ַ����̶������������õ��ڴ��С
����:ִ�гɹ��򽫽�����Ƶ�����buf��ָ���ڴ�ռ䣬���Ƿ����Զ����õ��ַ���ָ�롣ʧ�ܷ���NULL

int ftruncate(int fd,off_t length)
����˵��:������fdָ�����ļ���С��Ϊ����lengthָ���Ĵ�С;���ԭ�����ļ���С�Ȳ���length���򳬹��Ĳ��ֻᱻɾȥ
����:ִ�гɹ��򷵻�0��ʧ�ܷ���-1 
    EBADF ����fd�ļ�������Ϊ��Ч�Ļ���ļ��ѹرա�
    EINVAL ����fd Ϊһsocket �����ļ������Ǹ��ļ�������д��ģʽ��
    ��Ҫ���������ļ���дλ��: lseek(fd,0,SEEK_SET);����rewind

int link (const char *oldpath,const char *newpath)
����˵��:�Բ���newpathָ��������������һ���µ�����(Ӳ����)������oldpath��ָ�����Ѵ����ļ����������newpathָ��������Ϊһ�Ѵ��ڵ��ļ��򲻻Ὠ������
����:�ɹ��򷵻�0��ʧ�ܷ���-1,link()��������Ӳ�����޷���Խ��ͬ�ļ�ϵͳ�������Ҫ�����symlink

ͷ�ļ�
#include<sys/stat.h>
#include<unistd.h>
int stat(const char *file_name,struct stat *buf)
����˵��:��ȡ�ļ�״̬�����Ƶ�����buf��ָ�Ľṹ��
         stat�ṹ����:
            struct stat
            {
                dev_t st_dev; //�ļ��豸���
                ino_t st_ino; //inode
                mode_t st_mode; //�ļ������ͺʹ�ȡ��Ȩ��
                nlink_t st_nlink; //�������ļ���Ӳ������Ŀ���ս������ļ�ֵΪ1
                uid_t st_uid; //�ļ������ߵ��û�ʶ����
                gid_t st_gid; //�ļ������ߵ���ʶ����
                dev_t st_rdev; //�����ļ�Ϊװ���豸�ļ�����Ϊ���豸���
                off_t st_size; //total size, in bytes
                unsigned long st_blksize; //�ļ�ϵͳ��I/O��������С
                unsigned long st_blocks; //ռ���ļ�����ĸ�����ÿһ�����СΪ512 ���ֽ�
                time_t st_atime; //time of lastaccess:mknod��utime��read��write��tructateʱ�ı�
                time_t st_mtime; //time of last modification:mknod��utime��writeʱ�Ż�ı�
                time_t st_ctime; //time of last change:���������ļ������ߡ��顢Ȩ�ޱ�����ʱ����
            };
����:ִ�гɹ��򷵻�0��ʧ�ܷ���-1

int chmod(const char *path,mode_t mode)
����˵��:������mode Ȩ�������Ĳ���path ָ���ļ���Ȩ��
         ����mode:
            S_ISUID 04000 �ļ��ģ�set user-id on execution��λ
            S_ISGID 02000 �ļ��ģ�set group-id on execution��λ
            S_ISVTX 01000 �ļ���stickyλ
            S_IRUSR��S_IREAD�� 00400 �ļ������߾߿ɶ�ȡȨ��
            S_IWUSR��S_IWRITE��00200 �ļ������߾߿�д��Ȩ��
            S_IXUSR��S_IEXEC�� 00100 �ļ������߾߿�ִ��Ȩ��
            S_IRGRP 00040 �û���߿ɶ�ȡȨ��
            S_IWGRP 00020 �û���߿�д��Ȩ��
            S_IXGRP 00010 �û���߿�ִ��Ȩ��
            S_IROTH 00004 �����û��߿ɶ�ȡȨ��
            S_IWOTH 00002 �����û��߿�д��Ȩ��
            S_IXOTH 00001 �����û��߿�ִ��Ȩ��
����:Ȩ�޸ı�ɹ�����0��ʧ�ܷ���-1

ͷ�ļ�
#include<dirent.h>
int alphasort(const struct dirent **a,const struct dirent **b)
����˵��:����ĸ˳������Ŀ¼�ṹ;scandir������qsort����ʱ��Ϊ�жϵĺ���
dirent.d_type:DT_UNKNOWN = 0, DT_FIFO = 1, DT_CHR = 2, DT_DIR = 4,
              DT_BLK = 6, DT_REG = 8,DT_LNK = 10, DT_SOCK = 12

DIR *opendir(const char * name)
����˵��:�򿪲���nameָ����Ŀ¼��������DIR*��̬��Ŀ¼��,��������Ŀ¼�Ķ�ȡ��������Ҫʹ�ô˷���ֵ
����:�ɹ��򷵻�DIR* ��̬��Ŀ¼������ʧ���򷵻�NULL

struct dirent * readdir(DIR * dir)
����˵��:��ȡĿ¼
����:����dirĿ¼�����¸�Ŀ¼�����
        struct dirent
        {
            __ino_t d_ino; //��Ŀ¼������inode
            __off_t d_off; //Ŀ¼�ļ���ͷ����Ŀ¼������λ��
            unsigned short int d_reclen;//_name�ĳ��ȣ�������NULL�ַ�
            unsigned char d_type;//�ļ�����
            char d_name[256];//�ļ���
        };

int readlink(const char *path ,char *buf,size_t bufsiz)
����˵��:ȡ�÷���������ָ���ļ�·��,���浽������buf��ָ���ڴ�ռ�
����:�ַ������ַ�������(��Ҫ��Ϊ����\0)������bufsizС�ڷ������ӵ����ݳ��ȣ����������ݻᱻ�ض�

int rename(const char *oldpath, const char *newpath)
����˵��:������oldpath��ָ�����ļ����Ƹ�Ϊ����newpath��ָ���ļ����ơ���newpath��ָ�����ļ��Ѵ��ڣ�oldpath��ᱻɾ��
����:ִ�гɹ��򷵻�0��ʧ�ܷ���-1 (�൱��mv���old�ƶ���new��ʹ��new���֣�����Ϊold����)

int remove(const char *pathname)
����˵��:ɾ������pathnameָ�����ļ����������pathnameΪһ�ļ��������unlink()����������pathnameΪһĿ¼�������rmdir������

int unlink(const char *pathname)
����˵��:ɾ������pathnameָ�����ļ���������ļ���Ϊ������ӵ㣬�����������̴��˴��ļ����������й��ڴ��ļ����ļ������ʽԹرպ�Ż�ɾ����
         �������pathnameΪһ�������ӣ�������ӻᱻɾ��
����:�ɹ��򷵻�0��ʧ�ܷ���-1

ͷ�ļ�
#include<sys/types.h>
#include<utime.h>
int utime(const char *filename,struct utimbuf *buf)
����˵��:�޸Ĳ���filename�ļ�������inode��ȡʱ��;����bufΪ��ָ��(NULL)������ļ��Ĵ�ȡʱ��͸���ʱ��ȫ������ΪĿǰʱ��
     ����buf:
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
    fchdir(fd); //��ҪΪ·�������л�
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
        //�����ļ���Ŀ¼
        printf("d_name: %s\n",ptr->d_name);
    }
    closedir(dir);
}


/**************
���Խ��
****************/

/***************
ͬ���ͺ���:
int chdir(const char *path)//����ǰ�Ĺ���Ŀ¼�ı���Բ���path��ָ��Ŀ¼
int chroot(const char *path)//�ı��Ŀ¼Ϊ����path ��ָ����Ŀ¼��ֻ�г����û�������ı��Ŀ¼���ӽ��̽��̳��µĸ�Ŀ¼
int chown(const char *path, uid_t owner,gid_t group)//ָ���ļ��������߱��Ϊowner������û�,�ļ�������Ϊgroup��
int fchmod(int fildes,mode_t mode)//���Ĳ���fildes��ָ�ļ���Ȩ��,����mode��ο�chmod
int fchown(int fd,uid_t owner,gid_t group)//ָ���ļ��������߱��Ϊowner������û�,�ļ�������Ϊgroup��
int fstat(int fildes,struct stat *buf)//������fildes��ָ���ļ�״̬�����Ƶ�����buf��ָ�Ľṹ��(struct stat)
                  fstat��stat������ȫ��ͬ����ͬ�����ڴ���Ĳ���Ϊ�Ѵ򿪵��ļ�������
int fchdir(int fd)//��ǰ�Ĺ���Ŀ¼�ı���Բ���fd ��ָ���ļ�������
int lstat (const char *file_name.struct stat *buf)//ȡ�ò���file_name��ָ���ļ�״̬,���ļ�Ϊ��������ʱ,lstat�᷵�ظ�link�����״̬
int symlink( const char *oldpath,const char *newpath)//�Բ���newpathָ��������������һ���µ�����(��������)������oldpath��ָ�����Ѵ����ļ�
int truncate(const char *path,off_t length)//������path ָ�����ļ���С��Ϊ����length ָ���Ĵ�С�����ԭ�����ļ���С�Ȳ���length���򳬹��Ĳ��ֻᱻɾȥ
void rewinddir(DIR *dir)//���ò���dir Ŀ¼��Ŀǰ�Ķ�ȡλ��Ϊԭ����ͷ�Ķ�ȡλ�ã�readdir
void seekdir(DIR *dir,off_t offset)//���ò���dirĿ¼��Ŀǰ�Ķ�ȡλ�ã��ڵ���readdir()ʱ��Ӵ���λ�ÿ�ʼ��ȡ
off_t telldir(DIR *dir)//���ز���dirĿ¼��Ŀǰ�Ķ�ȡλ�á��˷���ֵ�������Ŀ¼�ļ���ͷ��ƫ����������ֵ�����¸���ȡλ��
int rmdir( const char *dirname )//ɾ��һ��Ŀ¼�����ɹ��򷵻�0�����򷵻�-1,ɾ���ļ�����-1
int utimes(char * filename.struct timeval *tvp)//�޸Ĳ���filename�ļ�������inode��ȡʱ����޸�ʱ��
               tvp[0].tc_sec��Ϊutimbuf.actime��tvp]1].tv_sec Ϊutimbuf.modtime
***************/

