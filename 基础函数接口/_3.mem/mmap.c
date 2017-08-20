/*************************
void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);
����˵����mmap()������ĳ���ļ�����ӳ�䵽�ڴ��У�
�Ը��ڴ�����Ĵ�ȡ����ֱ�ӶԸ��ļ����ݵĶ�д
����˵����
    start:ӳ����ڴ���ʵ��ַ��ͨ������Ϊ0����ʾ��ϵͳѡ�񡣳ɹ���ĵ�ַ�ᷴ��
	length:ӳ��ռ�Ĵ�С��ͬʱҲ�Ƕ�ȡ�ļ��Ĵ�С
    port:ӳ������ı�����ʽ
	    PROT_EXEC ӳ������ɱ�ִ��
		PROT_READ ӳ������ɱ���ȡ
		PROT_WRITE ӳ������ɱ�д��
		PROT_NONE ӳ�������ܴ�ȡ
    flags������ӳ����������
		MAP_FIXED �������start��ָ�ĵ�ַ�޷��ɹ�����ӳ��ʱ�������ӳ�䣬���Ե�ַ��������ͨ���������ô���ꡣ
		MAP_SHARED��ӳ�������д�����ݻḴ�ƻ��ļ��ڣ�������������ӳ����ļ��Ľ��̹���
		MAP_PRIVATE ��ӳ�������д����������һ��ӳ���ļ��ĸ��ƣ���˽�˵ġ�д��ʱ���ơ���copy on write���Դ����������κ��޸Ķ�����д��ԭ�����ļ����ݡ�
		MAP_ANONYMOUS��������ӳ�䡣��ʱ����Բ���fd�����漰�ļ�������ӳ�������޷����������̹���
		MAP_DENYWRITEֻ�����ӳ�������д��������������ļ�ֱ��д��Ĳ������ᱻ�ܾ���
		MAP_LOCKED ��ӳ����������ס�����ʾ�����򲻻ᱻ�û���swap����
    fdΪopen()���ص��ļ������ʣ�������ӳ�䵽�ڴ���ļ���
	offsetΪ�ļ�ӳ���ƫ������ͨ������Ϊ0��������ļ���ǰ����ʼ��Ӧ��offset�����Ƿ�ҳ��С����������
����ֵ:��ӳ��ɹ��򷵻�ӳ�������ڴ���ʼ��ַ�����򷵻�MAP_FAILED(��1)������ԭ�����errno ��


int msync ( void * addr , size_t len, int flags) 
һ��˵����������ӳ��ռ�ĶԹ������ݵĸı䲢��ֱ��д�ص������ļ��У������ڵ���munmap�������ִ�иò�����
����ͨ������msync()ʵ�ִ������ļ������빲���ڴ���������һ�¡� 

��������ʵ�ֽ��̼�ͨ��
#include <unistd.h>
#include <sys/mman.h>
**************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

 #include <fcntl.h>//O_RDONLY

#include <sys/types.h>//stat
#include <sys/stat.h>

int main()
{
	int fd;
	void *start;
	struct stat sb;
	fd=open("/etc/passwd",O_RDONLY); /*��/etc/passwd*/
	fstat(fd,&sb); /*ȡ���ļ���С*/
	/*
	off_t len;
	len = lseek(fd, 0, SEEK_END);
	*/
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if(start == MAP_FAILED) /*�ж��Ƿ�ӳ��ɹ�*/
	    return;
	printf("%p",start);
	munmap(start,sb.st_size); /*���ӳ��*/
	close(fd);
}

/**************
���Խ��
****************/

/***************
ͬ���ͺ���
***************/