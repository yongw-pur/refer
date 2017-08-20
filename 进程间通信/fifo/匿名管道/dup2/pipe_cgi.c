#include <stdio.h>  // printf  
#include <stdlib.h> // exit  
#include <unistd.h> // pipe  
#include <string.h> // strlen  
/*i'm confused that the input is not go to effect*/
  
int main()  
{  
	int status;
    int cgi_output[2];  
	int cgi_input[2];
	char buf[1024];
	int pid;
	char *path = "/tmp/a.sh";
    if (pipe(cgi_output) < 0)
	{
        printf("cannot open pipe\n");
		return;
	}
	if (pipe(cgi_input) < 0)
	{
		printf("cannot open pipe\n");
		return;
    }

    //创建一个子进程
    if ( (pid = fork()) < 0 ) 
	{
		printf("fork wrong\n");
		return;
	}
 
	//子进程用来执行 cgi 脚本
    if (pid == 0)  /* child: CGI script */
    {
		
		//dup2()包含<unistd.h>中，参读《TLPI》P97
		//将子进程的输出由标准输出重定向到 cgi_ouput 的管道写端上
		//将子进程的输出由标准输入重定向到 cgi_ouput 的管道读端上
		//关闭 cgi_ouput 管道的读端与cgi_input 管道的写端
		dup2(cgi_output[1], 1);//1输出，写 valid!
		dup2(cgi_input[0], 0);//invalid
		close(cgi_output[0]);
		close(cgi_input[1]);
		execl(path, "a.sh", NULL);
		exit(0);
	}
    else 
    {    /* parent */
	  //父进程则关闭了 cgi_output管道的写端和 cgi_input 管道的读端
	  close(cgi_output[1]);
	  close(cgi_input[0]);
      printf("write\n");
      write(cgi_input[1], "msg", strlen("msg"));
	   
	  //然后从 cgi_output 管道中读子进程的输出
	  read(cgi_output[0], buf, 1024);
      printf("buf is %s\n", buf);

	  //关闭管道
	  close(cgi_output[0]);
	  close(cgi_input[1]);
	  //等待子进程的退出
	  waitpid(pid, &status, 0);
	 }
}  