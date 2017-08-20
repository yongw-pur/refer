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

    //����һ���ӽ���
    if ( (pid = fork()) < 0 ) 
	{
		printf("fork wrong\n");
		return;
	}
 
	//�ӽ�������ִ�� cgi �ű�
    if (pid == 0)  /* child: CGI script */
    {
		
		//dup2()����<unistd.h>�У��ζ���TLPI��P97
		//���ӽ��̵�����ɱ�׼����ض��� cgi_ouput �Ĺܵ�д����
		//���ӽ��̵�����ɱ�׼�����ض��� cgi_ouput �Ĺܵ�������
		//�ر� cgi_ouput �ܵ��Ķ�����cgi_input �ܵ���д��
		dup2(cgi_output[1], 1);//1�����д valid!
		dup2(cgi_input[0], 0);//invalid
		close(cgi_output[0]);
		close(cgi_input[1]);
		execl(path, "a.sh", NULL);
		exit(0);
	}
    else 
    {    /* parent */
	  //��������ر��� cgi_output�ܵ���д�˺� cgi_input �ܵ��Ķ���
	  close(cgi_output[1]);
	  close(cgi_input[0]);
      printf("write\n");
      write(cgi_input[1], "msg", strlen("msg"));
	   
	  //Ȼ��� cgi_output �ܵ��ж��ӽ��̵����
	  read(cgi_output[0], buf, 1024);
      printf("buf is %s\n", buf);

	  //�رչܵ�
	  close(cgi_output[0]);
	  close(cgi_input[1]);
	  //�ȴ��ӽ��̵��˳�
	  waitpid(pid, &status, 0);
	 }
}  