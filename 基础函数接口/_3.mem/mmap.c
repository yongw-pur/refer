/*************************
void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);
函数说明：mmap()用来将某个文件内容映射到内存中，
对该内存区域的存取即是直接对该文件内容的读写
参数说明：
    start:映射的内存其实地址，通常设置为0，表示让系统选择。成功后改地址会反回
	length:映射空间的大小，同时也是读取文件的大小
    port:映射区域的保护方式
	    PROT_EXEC 映射区域可被执行
		PROT_READ 映射区域可被读取
		PROT_WRITE 映射区域可被写入
		PROT_NONE 映射区域不能存取
    flags：设置映射区域特性
		MAP_FIXED 如果参数start所指的地址无法成功建立映射时，则放弃映射，不对地址做修正。通常不鼓励用此旗标。
		MAP_SHARED对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享。
		MAP_PRIVATE 对映射区域的写入操作会产生一个映射文件的复制，即私人的“写入时复制”（copy on write）对此区域作的任何修改都不会写回原来的文件内容。
		MAP_ANONYMOUS建立匿名映射。此时会忽略参数fd，不涉及文件，而且映射区域无法和其他进程共享。
		MAP_DENYWRITE只允许对映射区域的写入操作，其他对文件直接写入的操作将会被拒绝。
		MAP_LOCKED 将映射区域锁定住，这表示该区域不会被置换（swap）。
    fd为open()返回的文件描述词，代表欲映射到内存的文件。
	offset为文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。
返回值:若映射成功则返回映射区的内存起始地址，否则返回MAP_FAILED(－1)，错误原因存于errno 中


int msync ( void * addr , size_t len, int flags) 
一般说来，进程在映射空间的对共享内容的改变并不直接写回到磁盘文件中，往往在调用munmap（）后才执行该操作。
可以通过调用msync()实现磁盘上文件内容与共享内存区的内容一致。 

可以用来实现进程间通信
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
	fd=open("/etc/passwd",O_RDONLY); /*打开/etc/passwd*/
	fstat(fd,&sb); /*取得文件大小*/
	/*
	off_t len;
	len = lseek(fd, 0, SEEK_END);
	*/
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if(start == MAP_FAILED) /*判断是否映射成功*/
	    return;
	printf("%p",start);
	munmap(start,sb.st_size); /*解除映射*/
	close(fd);
}

/**************
测试结果
****************/

/***************
同类型函数
***************/