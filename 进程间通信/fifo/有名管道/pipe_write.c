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
����˵��
mkfifo() ��������pathname���������FIFO�ļ������ļ����벻���ڣ�������modeΪ���ļ���Ȩ�ޣ�mode%~umask������� umaskֵҲ��Ӱ�쵽FIFO�ļ���Ȩ�ޡ�Mkfifo()������FIFO�ļ��������̶������ö�дһ���ļ��ķ�ʽ��ȡ����ʹ��open()���� FIFO�ļ�ʱ��O_NONBLOCK������Ӱ��
1����ʹ��O_NONBLOCK ���ʱ����FIFO �ļ�����ȡ�Ĳ��������̷��أ���������û���������̴�FIFO �ļ�����ȡ����д��Ĳ����᷵��ENXIO ������롣
2��û��ʹ��O_NONBLOCK ���ʱ����FIFO ����ȡ�Ĳ�����ȵ��������̴�FIFO�ļ���д����������ء�ͬ���أ���FIFO�ļ���д��Ĳ�����ȵ��������̴�FIFO �ļ�����ȡ����������ء�
����ֵ
���ɹ��򷵻�0�����򷵻�-1������ԭ�����errno�С�

ʹ�ùܵ����ж�дʱ���ȴ�д���̣�Ȼ����̻Ῠ��open�У�����noblock���������ȴ�������
Ȼ��򿪶����̣���ʱд���̿��Խ�������
*/