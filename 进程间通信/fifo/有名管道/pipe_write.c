#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define FIFO_NAME "/tmp/fifo"
#define BUF_LEN 12
 
 
int main(int argc, char *argv[])
{
    int pipeid = -1;
    int fifoid = -1;

    char buffer[BUF_LEN] = { "aaabbb" };
 

    if (access(FIFO_NAME, F_OK) < 0)
    {
		if((mkfifo(FIFO_NAME,O_CREAT|O_EXCL|O_RDWR)<0)&&(errno!=EEXIST))  
		{  
			printf("cannot create fifoserver\n");  
			return;
		}  
    }

    pipeid=open(FIFO_NAME,O_WRONLY);  
    if (pipeid < 0){         
		perror("open pipeid error\n");
        return -1;
     }

   /*int read_bytes = read(STDIN_FILENO, buffer, BUF_LEN);
	printf("rade byte %d\n", read_bytes);
    if (read_bytes < 0){
        perror("read error\n");
        close(pipeid);
        return -1;
    }

    const char * buff_send = buffer;
    int no_write_bytes = read_bytes;
    while (no_write_bytes > 0){
        int n = write(pipeid, buff_send, no_write_bytes);
        if (n < 0){
            perror("write error\n");
            close(pipeid);
            return -1;
        }
 
        no_write_bytes -= n;
        buff_send += n;
    }*/
    write(pipeid, buffer, BUF_LEN);
    close(pipeid);
 
    return 0;
}

/*
函数说明
mkfifo() 会依参数pathname建立特殊的FIFO文件，该文件必须不存在，而参数mode为该文件的权限（mode%~umask），因此 umask值也会影响到FIFO文件的权限。Mkfifo()建立的FIFO文件其他进程都可以用读写一般文件的方式存取。当使用open()来打开 FIFO文件时，O_NONBLOCK旗标会有影响
1、当使用O_NONBLOCK 旗标时，打开FIFO 文件来读取的操作会立刻返回，但是若还没有其他进程打开FIFO 文件来读取，则写入的操作会返回ENXIO 错误代码。
2、没有使用O_NONBLOCK 旗标时，打开FIFO 来读取的操作会等到其他进程打开FIFO文件来写入才正常返回。同样地，打开FIFO文件来写入的操作会等到其他进程打开FIFO 文件来读取后才正常返回。
返回值
若成功则返回0，否则返回-1，错误原因存于errno中。

使用管道进行读写时，先打开写进程，然后进程会卡在open中（设置noblock则会出错），等待读进程
然后打开读进程，此时写进程可以接收输入
*/