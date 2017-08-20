#include <stdio.h>  // printf  
#include <stdlib.h> // exit  
#include <unistd.h> // pipe  
#include <string.h> // strlen  
  
int main()  
{  
    int fd[2];  
	int pid = 0;  
	char str[] = "hello";  
	char readbuf[1024];  

	if(pipe(fd) < 0)  
	{  
		printf("pipe error!\n");  
	}  

	if((pid = fork()) < 0)  
	{  
		printf("fork error!\n");  
	}  
	else if(pid == 0)  
	{  
		printf("child process!\n");  
        
		// close read channel  
		close(fd[0]);  
		write(fd[1], str, strlen(str)); 
		//sleep(5); parent recieved the first msg will exit
		write(fd[1], str, strlen(str));
	}  
	else  
	{  
		printf("father process!\n");  
        //一般是父进程为读去的一方?
		//否则父进程接收，子进程还没有读到数据就退出了，但是最后还是会打印
		// close write channel  
		close(fd[1]);  
		read(fd[0], readbuf, sizeof(readbuf)); //read will block until fd has info
		printf("readbuf = %s\n", readbuf);  
	}  

	return 0;  
}  