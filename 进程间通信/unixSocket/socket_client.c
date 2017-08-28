 #include <stdio.h>
 #include <stddef.h>
 #include <sys/stat.h>
 #include <sys/socket.h>
 #include <sys/un.h>
 #include <errno.h>
 #include <string.h>
                                    
 #define msg_addr "sean_socket_addr"
 /* Create a client endpoint and connect to a server.   Returns fd if all OK, <0 on error. */
 int unix_socket_conn(const char *servername)
 { 
   int fd; 
   if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)    /* create a UNIX domain stream socket */ 
   {
     return(-1);
   }
   int len, rval;
    struct sockaddr_un un;          
	/* fill socket address structure with server's address */
	memset(&un, 0, sizeof(un)); 
	un.sun_family = AF_UNIX; 
	strcpy(un.sun_path, servername); 
	len = offsetof(struct sockaddr_un, sun_path) + strlen(servername); 
	
	if (connect(fd, (struct sockaddr *)&un, len) < 0) 
	{
	   rval= -4; 
	} 
	else
	{
	  return (fd);
	}
   int err;
   err = errno;
   close(fd); 
   errno = err;
   return rval;      
 }
  
  void unix_socket_close(int fd)
  {
     close(fd);     
  }
 
 
 int main(void)
 { 
   srand((int)time(0));
   int connfd; 
   connfd = unix_socket_conn(msg_addr);
   if(connfd<0)
   {
      printf("Error[%d] when connecting...",errno);
      return 0;
   }
    printf("Begin to recv/send...\n");  
   int i,n,size;
   char rvbuf[4096];
 /*
     //=========½ÓÊÕ=====================
     size = recv(connfd, rvbuf, 800, 0);   //MSG_DONTWAIT
      if(size>=0)
      {
         printf("Recieved Data[%d]:%c...%c\n",size,rvbuf[0],rvbuf[size-1]);
      }
      if(size==-1)
      {
          printf("Error[%d] when recieving Data.\n",errno);     
              break;        
      }
          if(size < 800) break;
 */
     //=========·¢ËÍ======================
     while(1)
     {
      memset(rvbuf,'a',32);
      rvbuf[22] = 'b';
      rvbuf[23] = 'b';
      rvbuf[24] = 'b';
      rvbuf[30] = 'b';
      rvbuf[31] = '0';
      size = send(connfd, rvbuf, 32, 0);
      if(size>=0)
      {
         printf("Data[%d] Sended:%c.\n",size,rvbuf[0]);
      }
      if(size==-1)
      {
         printf("Error[%d] when Sending Data:%s.\n",errno,strerror(errno));     
             break;        
      }
      sleep(5);
   }
    unix_socket_close(connfd);
    printf("Client exited.\n");    
  }