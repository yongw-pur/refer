/*************************
头文件
#include<unistd.h>
ssize_t read(int fd,void *buf ,size_t count)
函数说明:将fd所指的文件传送count个字节到buf指针所指的内存中
         若count为0，则read()不会有作用并返回0
返回:返回值为实际读取到的字节数，如果返回0，表示已到达文件尾或是无可读取的数据, 错误返回-1,并将根据不同的错误原因设置错误码,此外文件读写位置会随读取到的字节移动
read()会返回实际读到的字节数，最好能将返回值与参数count 作比较，若返回的字节数比要求读取的字节数少，则有可能读到了文件尾、从管道(pipe)或终端机读取，或者是read()被信号中断了读取动作。
当有错误发生时则返回-1，错误代码存入errno中，文件读写位置则无法预期
    EINTR 此调用被信号所中断。
    EAGAIN 当使用不可阻断I/O 时（O_NONBLOCK），若无数据可读取则返回此值。
    EBADF 参数fd 非有效的文件描述词，或该文件已关闭

ssize_t write (int fd,const void *buf,size_t count)
函数说明:把参数buf所指的内存写入count个字节到参数fd所指的文件内。文件读写位置也会随之移动
返回:write()会返回实际写入的字节数。当有错误发生时则返回-1，错误代码存入errno中,同read

头文件
#include<sys/types.h>
#include<unistd.h>
off_t lseek(int fildes,off_t offset ,int whence)
函数说明:控制该文件的读写位置。参数fildes 为已打开的文件描述词，参数offset 为根据参数whence来移动读写位置的位移数
         参数whence为参照地址:whence 值为SEEK_CUR 或SEEK_END时，参数offet允许负值的出现
            SEEK_SET 将读写位置指向文件头偏移offset为新的读写位置
            SEEK_CUR 以目前的读写位置往后增加offset个位移量
            SEEK_END 将读写位置指向文件尾后再增加offset个位移
 特别地:lseek（int fildes,0,SEEK_SET）将读写位置移到文件开头
        lseek（int fildes,0,SEEK_END）将读写位置移到文件尾
        lseek（int fildes,0,SEEK_CUR）取得目前文件位置
返回:当调用成功时则返回目前的读写位置，也就是距离文件开头多少个字节，若有错误则返回-1

int fgetc(FILE *stream)
函数说明:从参数stream所指的文件中读取一个字符。若读到文件尾而无数据时便返回EOF
返回值:getc()会返回读取到的字符，返回EOF则表示到了文件尾

char * fgets(char *s,int size,FILE *stream)
函数说明:从参数stream所指的文件内读入字符并存到参数s所指的内存空间
         直到出现换行字符、读到文件尾或是已读了size-1个字符为止，最后会加上NULL作为字符串结束
返回:成功则返回s指针，返回NULL则表示有错误发生

int ungetc(int c,FILE *stream)
函数说明:将参数c字符写回参数stream所指定的文件流。这个写回的字符会由下一个读取文件流的函数取得
返回:成功则返回c 字符，若有错误则返回EOF

size_t fread(void * ptr,size_t size,size_t nmemb,FILE * stream)
函数说明:从文件流中读取数据。参数stream为已打开的文件指针，参数ptr指向欲存放读取进来的数据空间，读取的字符数以参数size*nmemb来决定
返回:实际读取到的nmemb数目(如果此值比参数nmemb小，代表可能读到了文件尾或有错误发生，必须用feof()或ferror()来判断情况)

头文件
#include<stdio.h>
void clearerr(FILE *stream)
函数说明:清除参数stream指定的文件流所使用的错误旗标
当文件读取或写入出现错误时 最常见的是读到EOF导致出错,这时继续对文件指针进行读写会出错feof,包括移动文件指针,通过clearerr可以清除这个错误使文件操作可以继续执行
只要出现错误标志，就一直保留，直到对同一文件调用clearerr函数或rewind函数，或任何一个输入输出函数

int feof(FILE *stream)
函数说明:判断是否读取到了文件尾
返回:已到文件尾则返回非零值，否则返回0

void setbuf(FILE * stream,char * buf)
函数说明:在打开文件流后，读取内容之前，调用setbuf()可以用来设置文件流的缓冲区
         参数buf指向自定的缓冲区起始地址。如果参数buf为NULL指针，则为无缓冲IO
         setvbuf(stream,buf,buf?_IOFBF:_IONBF,BUFSIZ)

int setvbuf(FILE *stream,char *buf,int mode,size_t size)
函数说明:在打开文件流后，读取内容之前，调用setvbuf()可以用来设置文件流的缓冲区
         参数buf指向自定的缓冲区起始地址，参数size为缓冲区大小
         参数mode
            _IONBF 无缓冲IO,直接从流中读入数据或直接向流中写入数据，而没有缓冲区
            _IOLBF 以换行为依据的无缓冲IO 行模式工作,每写完一行(遇见\n),就会把整行真正的写到磁盘文件上，在遇到换行符前，都存在buffer中
            _IOFBF 满缓冲IO。当缓冲区为空时，从流读入数据。或者当缓冲区满时，向流写入数据;如果参数buf为NULL指针，则为无缓冲IO。

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
    offset = lseek(fileno(fp), 0, SEEK_END);  //第一次创建文件的时候，写入字符串还在缓存中,SEEK_END为0.
    c = fgetc(fp); //下标从0开始的
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
测试结果
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
同类型函数:(对文件流的操作函数相对较多--一般fread,fwrite用来读写二进制文件，读写结构体)
int getc(FILE *stream)//从参数stream所指的文件中读取一个字符。若读到文件尾而无数据时便返回EOF;getc()为宏定义，非真正的函数调用
int getchar(void)//从标准输入设备中读取一个字符。然后将该字符从unsigned char转换成int后返回;getchar()非真正函数，而是getc(stdin)宏定义
char * gets(char *s)//从标准设备读入字符并存到参数s所指的内存空间，直到出现换行字符或读到文件尾为止，最后加上NULL作为字符串结束.无法确定s的大小，建议使用fgets()取代
int putc(int c,FILE * stream)//将参数c转为unsigned char后写入参数stream指定的文件中；putc()为宏定义，非真正的函数调用
int putchar (int c)//putchar()用来将参数c字符写到标准输出设备，putchar()会返回输出成功的字符，即参数c；putchar()是putc(c，stdout)宏定义
int fputc(int c,FILE *stream) //将参数c转为unsigned char后写入参数stream 指定的文件中,返回写入成功的字符，即参数c。若返回EOF则代表写入失败
int fputs(const char *s,FILE *stream)//将参数s所指的字符串写入到参数stream所指的文件内,但不包括空字符('\0'),该函数返回一个非负值，如果发生错误则返回 EOF(-1)
size_t fwrite(const void *ptr,size_t size,size_t nmemb,FILE *stream)//将数据写入文件流中。参数stream为已打开的文件指针，参数ptr指向欲写入的数据地址，总共写入的字符数以参数size*nmemb来决定。
                        返回实际写入的nmemb数目
long ftell(FILE *stream)//获取文件流目前的读写位置，当调用成功时则返回目前的读写位置，若有错误则返回-1，errno会存放错误代码
int fseek(FILE *stream,long offset,int whence)//参数参考lseek,当调用成功时则返回0，若有错误则返回-1,fseek不会返回读写位置，必须使用ftell()来取得目前读写的位置
int ferror(FILE *stream)//调用各种输入输出函数（如putc.getc.fread.fwrite等)时，如果出现错误，除了函数返回值有所反映外，还可以用ferror函数检查。
                      如果ferror返回值为0（假），表示未出错。如果返回一个非零值，表示出错。对同一个文件每一次调用输入输出函数，均产生一个新的ferror值，应当在调用一个输入输出函数后立即检查ferror函数的值，否则信息会丢失。
                      在执行fopen函数时，ferror函数的初始值自动置为0;ferror不判断EOF错误
void rewind(FILE *stream)//把文件流的读写位置移至文件开头,fseek(stream,0,SEEK_SET)
void setbuffer(FILE *stream,char *buf,size_t size)//在打开文件流后，读取内容之前，调用setbuffer()可用来设置文件流的缓冲区
                     参数buf指向自定的缓冲区起始地址，参数size为缓冲区大小
***************/

