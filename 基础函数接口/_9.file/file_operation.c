/*************************
ͷ�ļ�
#include<unistd.h>
ssize_t read(int fd,void *buf ,size_t count)
����˵��:��fd��ָ���ļ�����count���ֽڵ�bufָ����ָ���ڴ���
         ��countΪ0����read()���������ò�����0
����:����ֵΪʵ�ʶ�ȡ�����ֽ������������0����ʾ�ѵ����ļ�β�����޿ɶ�ȡ������, ���󷵻�-1,�������ݲ�ͬ�Ĵ���ԭ�����ô�����,�����ļ���дλ�û����ȡ�����ֽ��ƶ�
read()�᷵��ʵ�ʶ������ֽ���������ܽ�����ֵ�����count ���Ƚϣ������ص��ֽ�����Ҫ���ȡ���ֽ����٣����п��ܶ������ļ�β���ӹܵ�(pipe)���ն˻���ȡ��������read()���ź��ж��˶�ȡ������
���д�����ʱ�򷵻�-1������������errno�У��ļ���дλ�����޷�Ԥ��
    EINTR �˵��ñ��ź����жϡ�
    EAGAIN ��ʹ�ò������I/O ʱ��O_NONBLOCK�����������ݿɶ�ȡ�򷵻ش�ֵ��
    EBADF ����fd ����Ч���ļ������ʣ�����ļ��ѹر�

ssize_t write (int fd,const void *buf,size_t count)
����˵��:�Ѳ���buf��ָ���ڴ�д��count���ֽڵ�����fd��ָ���ļ��ڡ��ļ���дλ��Ҳ����֮�ƶ�
����:write()�᷵��ʵ��д����ֽ��������д�����ʱ�򷵻�-1������������errno��,ͬread

ͷ�ļ�
#include<sys/types.h>
#include<unistd.h>
off_t lseek(int fildes,off_t offset ,int whence)
����˵��:���Ƹ��ļ��Ķ�дλ�á�����fildes Ϊ�Ѵ򿪵��ļ������ʣ�����offset Ϊ���ݲ���whence���ƶ���дλ�õ�λ����
         ����whenceΪ���յ�ַ:whence ֵΪSEEK_CUR ��SEEK_ENDʱ������offet����ֵ�ĳ���
            SEEK_SET ����дλ��ָ���ļ�ͷƫ��offsetΪ�µĶ�дλ��
            SEEK_CUR ��Ŀǰ�Ķ�дλ����������offset��λ����
            SEEK_END ����дλ��ָ���ļ�β��������offset��λ��
 �ر��:lseek��int fildes,0,SEEK_SET������дλ���Ƶ��ļ���ͷ
        lseek��int fildes,0,SEEK_END������дλ���Ƶ��ļ�β
        lseek��int fildes,0,SEEK_CUR��ȡ��Ŀǰ�ļ�λ��
����:�����óɹ�ʱ�򷵻�Ŀǰ�Ķ�дλ�ã�Ҳ���Ǿ����ļ���ͷ���ٸ��ֽڣ����д����򷵻�-1

int fgetc(FILE *stream)
����˵��:�Ӳ���stream��ָ���ļ��ж�ȡһ���ַ����������ļ�β��������ʱ�㷵��EOF
����ֵ:getc()�᷵�ض�ȡ�����ַ�������EOF���ʾ�����ļ�β

char * fgets(char *s,int size,FILE *stream)
����˵��:�Ӳ���stream��ָ���ļ��ڶ����ַ����浽����s��ָ���ڴ�ռ�
         ֱ�����ֻ����ַ��������ļ�β�����Ѷ���size-1���ַ�Ϊֹ���������NULL��Ϊ�ַ�������
����:�ɹ��򷵻�sָ�룬����NULL���ʾ�д�����

int ungetc(int c,FILE *stream)
����˵��:������c�ַ�д�ز���stream��ָ�����ļ��������д�ص��ַ�������һ����ȡ�ļ����ĺ���ȡ��
����:�ɹ��򷵻�c �ַ������д����򷵻�EOF

size_t fread(void * ptr,size_t size,size_t nmemb,FILE * stream)
����˵��:���ļ����ж�ȡ���ݡ�����streamΪ�Ѵ򿪵��ļ�ָ�룬����ptrָ������Ŷ�ȡ���������ݿռ䣬��ȡ���ַ����Բ���size*nmemb������
����:ʵ�ʶ�ȡ����nmemb��Ŀ(�����ֵ�Ȳ���nmembС��������ܶ������ļ�β���д�������������feof()��ferror()���ж����)

ͷ�ļ�
#include<stdio.h>
void clearerr(FILE *stream)
����˵��:�������streamָ�����ļ�����ʹ�õĴ������
���ļ���ȡ��д����ִ���ʱ ������Ƕ���EOF���³���,��ʱ�������ļ�ָ����ж�д�����feof,�����ƶ��ļ�ָ��,ͨ��clearerr��������������ʹ�ļ��������Լ���ִ��
ֻҪ���ִ����־����һֱ������ֱ����ͬһ�ļ�����clearerr������rewind���������κ�һ�������������

int feof(FILE *stream)
����˵��:�ж��Ƿ��ȡ�����ļ�β
����:�ѵ��ļ�β�򷵻ط���ֵ�����򷵻�0

void setbuf(FILE * stream,char * buf)
����˵��:�ڴ��ļ����󣬶�ȡ����֮ǰ������setbuf()�������������ļ����Ļ�����
         ����bufָ���Զ��Ļ�������ʼ��ַ���������bufΪNULLָ�룬��Ϊ�޻���IO
         setvbuf(stream,buf,buf?_IOFBF:_IONBF,BUFSIZ)

int setvbuf(FILE *stream,char *buf,int mode,size_t size)
����˵��:�ڴ��ļ����󣬶�ȡ����֮ǰ������setvbuf()�������������ļ����Ļ�����
         ����bufָ���Զ��Ļ�������ʼ��ַ������sizeΪ��������С
         ����mode
            _IONBF �޻���IO,ֱ�Ӵ����ж������ݻ�ֱ��������д�����ݣ���û�л�����
            _IOLBF �Ի���Ϊ���ݵ��޻���IO ��ģʽ����,ÿд��һ��(����\n),�ͻ������������д�������ļ��ϣ����������з�ǰ��������buffer��
            _IOFBF ������IO����������Ϊ��ʱ�������������ݡ����ߵ���������ʱ������д������;�������bufΪNULLָ�룬��Ϊ�޻���IO��

**************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

main()
{
    char c;
    FILE *fp;
    int offset;
    int count;
    
    fp = fopen("noexist","a+");
    if(fp == NULL) 
        return;
    fprintf(fp, "hello!");
    fflush(fp);
    offset = lseek(fileno(fp), 0, SEEK_SET);
    printf("SEEK_SET 0 offset %d\n", offset);
    offset = lseek(fileno(fp), 0, SEEK_CUR);
    printf("SEEK_CUR 0 offset %d\n", offset);
    offset = lseek(fileno(fp), 0, SEEK_END);  //��һ�δ����ļ���ʱ��д���ַ������ڻ�����,SEEK_ENDΪ0.
    c = fgetc(fp); //�±��0��ʼ��
    printf("SEEK_END 0 offset %d\n", offset);
    printf("fgetc(fp) %d feof %d\n", c, feof(fp));
    count = ftell(fp);
    printf("ftell %d\n", count);
    offset = lseek(fileno(fp), -6, SEEK_END);
    printf("SEEK_END 6 offset %d feof %d\n", offset, feof(fp));

    rewind(fp);
    printf("rewind feof %d\n", feof(fp));
    while((c=fgetc(fp))!=EOF)
        printf("%c",c); 
    printf("feof %d\n", feof(fp));
    clearerr(fp);
    printf("clearerr feof %d\n", feof(fp));
    fclose(fp);

    char s[80];
    fputs(fgets(s, 80, stdin), stdout);
}


/**************
���Խ��
SEEK_SET 0 offset 0
SEEK_CUR 0 offset 0
SEEK_END 0 offset 12
fgetc(fp) -1 feof 1
ftell 12
SEEK_END 6 offset 6 feof 1
rewind feof 0
hello!hello!feof 1
clearerr feof 0
1234
1234
****************/

/***************
ͬ���ͺ���:(���ļ����Ĳ���������Խ϶�--һ��fread,fwrite������д�������ļ�����д�ṹ��)
int getc(FILE *stream)//�Ӳ���stream��ָ���ļ��ж�ȡһ���ַ����������ļ�β��������ʱ�㷵��EOF;getc()Ϊ�궨�壬�������ĺ�������
int getchar(void)//�ӱ�׼�����豸�ж�ȡһ���ַ���Ȼ�󽫸��ַ���unsigned charת����int�󷵻�;getchar()����������������getc(stdin)�궨��
char * gets(char *s)//�ӱ�׼�豸�����ַ����浽����s��ָ���ڴ�ռ䣬ֱ�����ֻ����ַ�������ļ�βΪֹ��������NULL��Ϊ�ַ�������.�޷�ȷ��s�Ĵ�С������ʹ��fgets()ȡ��
int putc(int c,FILE * stream)//������cתΪunsigned char��д�����streamָ�����ļ��У�putc()Ϊ�궨�壬�������ĺ�������
int putchar (int c)//putchar()����������c�ַ�д����׼����豸��putchar()�᷵������ɹ����ַ���������c��putchar()��putc(c��stdout)�궨��
int fputc(int c,FILE *stream) //������cתΪunsigned char��д�����stream ָ�����ļ���,����д��ɹ����ַ���������c��������EOF�����д��ʧ��
int fputs(const char *s,FILE *stream)//������s��ָ���ַ���д�뵽����stream��ָ���ļ���,�����������ַ�('\0'),�ú�������һ���Ǹ�ֵ��������������򷵻� EOF(-1)
size_t fwrite(const void *ptr,size_t size,size_t nmemb,FILE *stream)//������д���ļ����С�����streamΪ�Ѵ򿪵��ļ�ָ�룬����ptrָ����д������ݵ�ַ���ܹ�д����ַ����Բ���size*nmemb��������
                        ����ʵ��д���nmemb��Ŀ
long ftell(FILE *stream)//��ȡ�ļ���Ŀǰ�Ķ�дλ�ã������óɹ�ʱ�򷵻�Ŀǰ�Ķ�дλ�ã����д����򷵻�-1��errno���Ŵ������
int fseek(FILE *stream,long offset,int whence)//�����ο�lseek,�����óɹ�ʱ�򷵻�0�����д����򷵻�-1,fseek���᷵�ض�дλ�ã�����ʹ��ftell()��ȡ��Ŀǰ��д��λ��
int ferror(FILE *stream)//���ø������������������putc.getc.fread.fwrite��)ʱ��������ִ��󣬳��˺�������ֵ������ӳ�⣬��������ferror������顣
                      ���ferror����ֵΪ0���٣�����ʾδ�����������һ������ֵ����ʾ������ͬһ���ļ�ÿһ�ε����������������������һ���µ�ferrorֵ��Ӧ���ڵ���һ����������������������ferror������ֵ��������Ϣ�ᶪʧ��
                      ��ִ��fopen����ʱ��ferror�����ĳ�ʼֵ�Զ���Ϊ0;ferror���ж�EOF����
void rewind(FILE *stream)//���ļ����Ķ�дλ�������ļ���ͷ,fseek(stream,0,SEEK_SET)
void setbuffer(FILE *stream,char *buf,size_t size)//�ڴ��ļ����󣬶�ȡ����֮ǰ������setbuffer()�����������ļ����Ļ�����
                     ����bufָ���Զ��Ļ�������ʼ��ַ������sizeΪ��������С
***************/

