#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h> //offsetof 
#include <string.h>

#define msg_addr "sean_socket_addr"
#define MAX_CONNECTION_NUMBER 5
fd_set sg_readfs;

int Sean_Init_Socket()
{
    int fd, len;
    struct sockaddr_un un;
    
    memset(&un, 0, sizeof(un));  
    
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
		printf("Sean>>> socket create error\n");
		return -1;    	
    }
    
	un.sun_family = AF_UNIX; 
	strcpy(un.sun_path, msg_addr);
	unlink(un.sun_path); 
	//get the len of struct including msg_addr
	//offsetof: get the offsetlen of member in the struct
	len = offsetof(struct sockaddr_un, sun_path) + strlen(msg_addr); 
	
	/* bind the name to the descriptor */ 
	if (bind(fd, (struct sockaddr *)&un, len) < 0)
	{ 
		printf("Sean>>> socket bind error\n");
		close(fd);
		return -1;
	} 
	
    if (listen(fd, MAX_CONNECTION_NUMBER) < 0)    
    { 
    	printf("Sean>>> socket listen error\n");
        close(fd);
        return -1;
    }
     
    return fd;
}

int main()
{
	int server_fd;
	int max_fd = 0;
	int loop = 1;
	int ret, i;
	struct timeval tm;
	fd_set readfs;
	
	FD_ZERO(&sg_readfs);
	tm.tv_sec  = 5;
    tm.tv_usec = 0;
	server_fd = Sean_Init_Socket();
	
	//set readfs bit , watch it later
	FD_SET(server_fd, &sg_readfs);
	//update select creial
	max_fd = (server_fd > max_fd)? server_fd: max_fd;
	
	while(loop)
	{
	    tm.tv_sec  = 5;
	    tm.tv_usec = 0;
		readfs = sg_readfs;
		ret = select(max_fd + 1, &readfs, NULL, NULL, &tm);
		if(ret < 0)
		{
			if (errno != EINTR )
			{
				printf("Sean>>> select returned %d errno=%d\n", ret, errno);
			}
			continue;
		}
		if (ret  == 0)
		{
			printf("Sean>>> time out\n");
			continue;	
		}
		
		for (i = 0; i < max_fd + 1; i++)
    	{
        	if (!FD_ISSET(i, &readfs))
        	{
           		continue;
        	}
        	
        	printf("Sean>>> get msg i%d!\n", i);
        	if (i == server_fd)
        	{
        		int client_fd;
        		int sock_addr_size;
        		struct sockaddr_un clientAddr;
        		
        		sock_addr_size = sizeof(clientAddr);
	        	if ((client_fd = accept(server_fd, (struct sockaddr *)&clientAddr, &sock_addr_size)) < 0)
	            {
	                printf("Sean>>> accept ERROR!\n");
	            }
	            else
	            {
	            	FD_SET(client_fd, &sg_readfs);	
	            	max_fd = (client_fd > max_fd)? client_fd: max_fd;
	            }
        	}
        	else
        	{
        		char recv_buf[1024];
		        memset(recv_buf,0,1024);  
		        int num=read(i,recv_buf,sizeof(recv_buf)); 
		        if (num == 0)
		        {
		        	printf("Sean>>> client close it/n");  
		        	FD_CLR(i, &sg_readfs);
		        }
		        else
		        {
		       		printf("Message from client (%d)) :%s/n",num,recv_buf);  
		        }
        	}
        }
	}
}