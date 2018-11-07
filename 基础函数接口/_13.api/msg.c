/*************************
头文件
#include<netdb.h>
int getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
函数说明:hostname:一个主机名或者地址串(IPv4的点分十进制串或者IPv6的16进制串)
         service：一个服务名或者10进制端口号数串。
         hints:可以是一个空指针，也可以是一个指向某个addrinfo结构的指针，调用者在这个结构中填入关于期望返回的信息类型的暗示
                 例如:如果指定的服务既支持TCP也支持UDP，那么调用者可以把hints结构中的ai_socktype成员设置成SOCK_DGRAM使得返回的仅仅是适用于数据报套接口的信息。
         result指针:参数返回一个指向addrinfo结构链表的指针
    struct addrinfo
    {
      int ai_flags;	//Input flags
        AI_PASSIVE	套接字地址将用于调用bind 函数;当节点名位NULL，且此标志置位，则返回的地址将是通配地址;如果节点名NULL，且此标志不置位，则返回的地址将是回环地址。
        AI_CANONNAME	返回规范名称
        AI_NUMERICHOST	传递给getaddrinfo函数的nodename参数必须是数字字符串。
        AI_ALL	If this bit is set, a request is made for IPv6 addresses and IPv4 addresses with AI_V4MAPPED.
        AI_ADDRCONFIG	只有配置了全局地址后，getaddrinfo才会解析。 IPv6和IPv4环回地址不被认为是有效的全局地址。
        AI_V4MA PPED	如果对IPv6地址的getaddrinfo请求失败，则对IPv4地址进行名称服务请求，这些地址将转换为IPv4映射IPv6地址格式。
        AI_NON_AUTHORITATIVE	地址信息可以来自非授权命名空间提供商
        AI_SECURE	地址信息来自安全信道。
        AI_RETURN_PREFERRED_NAMES	地址信息是用于用户的优选名称。
        AI_FQDN	getaddrinfo将返回名称最终解析为的完全限定域名。 完全限定域名在ai_canonname成员中返回。
        这与AI_CANONNAME位标记不同，后者返回在DNS中注册的规范名称，该名称可能与平面名称解析为的完全限定域名不同。
        只能设置AI_FQDN和AI_CANONNAME位中的一个,如果EAI_BADFLAGS同时存在这两个标志，getaddrinfo函数将失败。
        AI_FILESERVER	命名空间提供程序提示正在查询的主机名正在文件共享方案中使用。 命名空间提供程序可以忽略此提示。
      int ai_family;//Protocol family for socket: AF_INET(IPv4),AF_INET6(IPv6),AF_UNSPEC(协议无关)
      int ai_socktype;//Socket type:SOCK_STREAM(数据流,TCP),SOCK_DGRAM(数据报,UDP)
      int ai_protocol;//Protocol for socket:IPPROTO_TCP传输控制协议（TCP）,IPPROTO_UDP用户数据报协议（UDP）ai_protocol指定了值0，则调用者不希望指定协议，服务提供者将选择要使用的ai_protocol
      socklen_t ai_addrlen;	//Length of socket address. 指向的缓冲区的长度（以字节为单位）
      struct sockaddr *ai_addr;	//Socket address for socket.指向 sockaddr 结构的指针。每个返回的addrinfo结构中的ai_addr成员指向一个填充的套接字地址结构。每个返回的addrinfo结构的长度（以字节为单位）在ai_addrlen成员中指定
      char *ai_canonname;//Canonical name for service location. 主机的规范名称
      struct addrinfo *ai_next;	//Pointer to next in list
     }; 
     struct sockaddr 
     {
        ushort  sa_family;
        char    sa_data[14];
     };
1.如果与node参数关联的地址有多个，那么适用于所请求地址簇的每个地址都返回一个对应的结构。
2.如果service参数指定的服务支持多个套接口类型，那么每个套接口类型都可能返回一个对应的结构，具体取决于hints结构的ai_socktype成员
函数的前两个参数分别是节点名和服务名。节点名可以是主机名，也可以是地址串(IPv4的点分十进制数表示或IPv6的十六进制数字串)。服务名可以是十进制的端口号，也可以是已定义的服务名称，如ftp、http等

通常服务器端在调用getaddrinfo之前，ai_flags设置AI_PASSIVE，用于bind；主机名nodename通常会设置为NULL，返回通配地址[::]

int recvmsg(int s,struct msghdr *msg,unsigned int flags)
函数说明:接收远程主机经指定的socket传来的数据。参数s为已建立好连线的socket，如果利用UDP协议则不需经过连线操作。参数msg指向欲连线的数据结构内容，参数flags一般设0
        struct msghdr
        {
            void *msg_name; //Address to send to /receive from:存数据包的目的地址，网络包指向struct sockaddr_in,向内核发数据时，指向struct sockaddr_nl
            socklen_t msg_namelen; //Length of addres data
            strcut iovec * msg_iov; //Vector of data to send/receive into
            size_t msg_iovlen; //Number of elements in the vector
            void * msg_control; //Ancillary dat
            size_t msg_controllen; //Ancillary data buffer length
            int msg_flags; //Flags on received message
        };
        msg_name 和 msg_namelen 这两个成员用于套接字未连接的场合:如未连接 UDP 套接字,它们类似 recvfrom 和 sendto 的第五个和第六个参数
        msg_iov 和 msg_iovlen这两个成员指定输入或输出缓冲区数组（即iovec结构数组）
        msg_control 和 msg_controllen 这两个成员指定可选的辅助数据的位置和大小
        只有recvmsg使用msg_flags成员。recvmsg被调用时，flags参数被拷贝到msg_flags成员，并由内核使用其值驱动接收处理过程

        控制信息头部
        struct cmsghdr 
        {
             socklen_t cmsg_len; //附属数据的字节计数，这包含结构头的尺寸。这个值是由CMSG_LEN()宏计算的
             int       cmsg_level; //表明了原始的协议级别(例如，SOL_SOCKET)
             int       cmsg_type;  //表明了控制信息类型(例如，SCM_RIGHTS:附属数据对象是一个文件描述符)
        };

struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *msgh);//返回一个指向附属数据缓冲区内的第一个附属对象的struct cmsghdr指针
        这个宏会估计msghdr的成员msg_control与msg_controllen来确定在缓冲区中是否存在附属对象。然后，他会计算返回的指针。
        如果不存在附属数据对象则返回的指针值为NULL。否则，这个指针会指向存在的第一个struct cmsghdr
struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh, struct cmsghdr *cmsg);//
        返回下一个附属数据对象的struct cmsghdr指针。这个宏会接受两个输入参数：
        指向struct msghdr结构的指针
        指向当前struct cmsghdr的指针
        如果没有下一个附属数据对象，这个宏就会返回NULL
size_t CMSG_ALIGN(size_t length);//指定一个字节长度作为输入，这个宏会计算一个新的长度，这个新长度包括为了维护对齐所需要的额外的填充字节
size_t CMSG_SPACE(size_t length);//计算附属数据以及其头部所需的总空白
size_t CMSG_LEN(size_t length);//接受我们希望放置在附属数据缓冲区中的对象尺寸作为输入参数
        计算cmsghdr头结构加上所需要的填充字符的字节长度，用来设置cmsghdr对象的cmsg_len成员，CMSG_LEN()值并不包括可能的结尾的填充字符
void *CMSG_DATA(struct cmsghdr *cmsg);//返回的指针值指向跟随在头部以及填充字节之后的附属数据的第一个字节(如果存在)

获取cmsghdr数据
struct msghdr msgh;     
struct cmsghdr *cmsg; 
int *fd_ptr;            
int received_fd;        
for ( cmsg=CMSG_FIRSTHDR(&msgh); cmsg!=NULL; cmsg=CMSG_NXTHDR(&msgh,cmsg) ) {
    if ( cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS ) {
        fd_ptr = (int *) CMSG_DATA(cmsg);
        received_fd = *fd_ptr;
        break;
    }
}

构造cmsghdr数据
int fd;   
struct msghdr msg;            
struct cmsghdr *cmsg;
           
char buf[CMSG_SPACE(sizeof fd)];
int *fd_ptr;           
msg.msg_control = buf;
msg.msg_controllen = sizeof buf;
cmsg = CMSG_FIRSTHDR(&msg);
cmsg->cmsg_level = SOL_SOCKET;
cmsg->cmsg_type = SCM_RIGHTS;
cmsg->cmsg_len = CMSG_LEN(sizeof fd);

fd_ptr = (int *)CMSG_DATA(cmsg);
*fd_ptr = fd;
msg.msg_controllen = cmsg->cmsg_len;

int readv(int fd, const struct iovec *vector, int count)
int writev(int fd, const struct iovec *vector, int count)
fd是要在其上进行读或是写的文件描述符fd,vector是读或写所用的I/O向量,count是要使用的向量元素个数


nlmsghdr数据:
NLMSG_SPACE(MAX_PAYLOAD)该宏用于返回不小于MAX_PAYLOAD且4字节对齐的最小长度值，一般用于向内存系统申请空间是指定所申请的内存字节数
NLMSG_LENGTH(len)消息负载和消息头加起来的总长度。
NLMSG_DATA(nlh)返回Netlink消息中数据部分的首地址

len = recvmsg(nl_sock, &msg, 0);
for (nh = (struct nlmsghdr *)buf; NLMSG_OK(nh, len); nh = NLMSG_NEXT (nh, len))

struct msghdr msg; 
memset(&msg, 0, sizeof(msg));
msg.msg_name = (void *)&(nladdr);
msg.msg_namelen = sizeof(nladdr);
char buffer[] = "An example message";
struct nlmsghdr nlhdr;
nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));
strcpy(NLMSG_DATA(nlhdr),buffer);//将数据存放在消息头指向的数据地址
nlhdr->nlmsg_len = NLMSG_LENGTH(strlen(buffer));
nlhdr->nlmsg_pid = getpid(); 
nlhdr->nlmsg_flags = 0;
iov.iov_base = (void *)nlhdr;
iov.iov_len = nlh->nlmsg_len;
msg.msg_iov = &iov;
msg.msg_iovlen = 1;

**************************/
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/wait.h>
    
#define BUFSIZE 4096
#define LISTENQ 100
    
void sig_child(int signo) {
    int ppid;
    while ((ppid = waitpid(-1,NULL,WNOHANG)) > 0) {
        printf("child process: %d terminated\n",ppid);
    }
}

void server_echo(int fd) {
    char recv[BUFSIZE];
    int n;
    struct msghdr rvmsg;
    struct iovec io;
    struct sockaddr_storage from;
    struct cmsghdr control;
    io.iov_base = recv;
    io.iov_len = BUFSIZE;
    rvmsg.msg_name = &from;
    rvmsg.msg_iov = &io;
    rvmsg.msg_iovlen = 1;
    rvmsg.msg_control = &control;
    rvmsg.msg_controllen = sizeof(struct cmsghdr);
    struct msghdr sdmsg;
    while ((n = recvmsg(fd,&rvmsg,0)) > 0) {
        sdmsg.msg_name = rvmsg.msg_name;
        sdmsg.msg_namelen = rvmsg.msg_namelen;
        sdmsg.msg_iov = &io;
        sdmsg.msg_iovlen = 1;
        sdmsg.msg_control = NULL;
        sdmsg.msg_controllen = 0;
        sdmsg.msg_flags = 0;
        io.iov_len = n;
        if (sendmsg(fd,&sdmsg,0) != n) {
            printf("send message to client failed: %s\n",strerror(errno));
            exit(1);
        }
        io.iov_len = BUFSIZE;
    }
}

int main(int argc,char** argv) 
{
    if (argc != 2) {
        printf("please check <service name or port>\n");
        exit(1);
    }

    struct addrinfo hints;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* results;
    int err;
    if ((err = getaddrinfo(NULL,argv[1],&hints,&results)) != 0) {
        printf("getaddrinfo error: %s\n",gai_strerror(err));
        exit(1);
    }
    struct addrinfo* dummy = results;
    int sockfd;
    for (; dummy != NULL; dummy = dummy->ai_next) {
        if ((sockfd = socket(dummy->ai_family,dummy->ai_socktype,dummy->ai_protocol)) < 0) {
            continue;
        }
        if (bind(sockfd,dummy->ai_addr,dummy->ai_addrlen) == 0) {
            break;
        }
        close(sockfd);
    }
    if (dummy == NULL) {
        freeaddrinfo(results);
        printf("all failed\n");
        exit(1);
    }
    freeaddrinfo(results);
    if (listen(sockfd,LISTENQ) < 0) {
        printf("listen error: %s\n",strerror(errno));
        exit(1);
    }
    int connfd;
    int pid;
    if (signal(SIGCHLD,sig_child) == SIG_ERR) {
        printf("signal error: %s\n",strerror(errno));
        exit(1);
    }
    for (; ;) {
        if ((connfd = accept(sockfd,NULL,NULL)) < 0) {
            if (errno == EINTR) {
                continue;
            }else {
                printf("accept error: %s\n",strerror(errno));
                exit(1);
            }
        }
        if ((pid = fork()) < 0) {
            printf("fork error: %s\n",strerror(errno));
            exit(1);
        }else if (pid == 0) {
            close(sockfd);
            server_echo(connfd);
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#define BUFSIZE 4096

void client_echo(int fd,struct sockaddr_storage* to,socklen_t tolen) {
    char send[BUFSIZE];
    int n;
    struct msghdr sdmsg,rvmsg;
    struct iovec io;
    io.iov_base = send;
    sdmsg.msg_name = to;
    sdmsg.msg_namelen = tolen;
    sdmsg.msg_iov = &io;
    sdmsg.msg_iovlen = 1;
    sdmsg.msg_control = NULL;
    sdmsg.msg_controllen = 0;
    sdmsg.msg_flags = 0;

    struct sockaddr_storage from;
    struct cmsghdr control;
    rvmsg.msg_name = &from;
    rvmsg.msg_control = &control;
    rvmsg.msg_controllen = sizeof(struct cmsghdr);
    rvmsg.msg_iov = &io;
    rvmsg.msg_iovlen = 1;
    rvmsg.msg_flags = 0;
    while ((n = read(STDIN_FILENO,send,BUFSIZE)) > 0) {
        io.iov_len = n;
        if (sendmsg(fd,&sdmsg,0) != n) {
            printf("send message to server error: %s\n",strerror(errno));
            exit(1);
        }
        io.iov_len = BUFSIZE;
        if ((n = recvmsg(fd,&rvmsg,0)) < 0) {
            printf("get from server fail: %s\n",strerror(errno));
            exit(1);
        }
        if (write(STDOUT_FILENO,send,n) != n) {
            printf("write error: %s\n",strerror(errno));
            exit(1);
        }
    }
}

int main(int argc,char** argv) 
{
    if (argc != 3) {
        printf("please check <ip address or host name> <service name or host name>\n");
        exit(1);
    }

    struct addrinfo hints;
    bzero(&hints,sizeof(struct addrinfo));

    hints.ai_flags = AI_ALL;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* results;
    int err;
    if ((err = getaddrinfo(argv[1],argv[2],&hints,&results)) != 0) {
        printf("getaddrinfo error: %s\n",gai_strerror(errno));
        exit(1);
    }

    struct addrinfo* dummy = results;
    int sockfd;
    for (; dummy != NULL; dummy = dummy->ai_next) {
        if ((sockfd = socket(dummy->ai_family,dummy->ai_socktype,dummy->ai_protocol)) < 0) {
            continue;
        }
        if (connect(sockfd,dummy->ai_addr,dummy->ai_addrlen) == 0) {
            break;
        }
        close(sockfd);
    }

    if (dummy == NULL) {
        freeaddrinfo(results);
        printf("all connect failed\n");
        exit(1);
    }
    client_echo(sockfd,(struct sockaddr_storage*)dummy->ai_addr,dummy->ai_addrlen);
    freeaddrinfo(results);
    return 0;
}
#endif

#if 0
int eunetlink_recv(int sock)
{ 
    struct sockaddr_nl nladdr;  
    struct msghdr msg;  
    struct iovec iov[1];  
    struct nlmsghdr * nlh;    
    char buffer[65536]; /*临时buffer，用于接收内核发过来的数据*/  
    int len;       
 
    /*填充待接收消息结构体*/ 
    msg.msg_name = (void *)&(nladdr);  /*设定接收的发送源地址*/   
    msg.msg_namelen = sizeof(nladdr);  
 
    /*设定临时缓冲*/
    iov[0].iov_base = (void *)buffer; 
    iov[0].iov_len = sizeof(buffer);
    msg.msg_iov = iov;                    
    msg.msg_iovlen = sizeof(iov)/sizeof(iov[0]);  /*允许多个临时缓冲*/
    
    len = recvmsg(sock, &msg, 0);  /*阻塞等待接收数(除非特别设定，socket都是阻塞式接收)*/
    if (len < 0) { 
        printf("recvmsg error: %d", len);     
        return len; 
    }       
 
    /*遍历接收到的消息数据，进行处理
        NLMSG_OK会判断数据是不是已经结束
        NLMSG_NEXT 会修改nlh和len的值，使之指向buffer中的下一个netlink消息
       */     
    for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, len); nlh = NLMSG_NEXT(nlh, len)) {  
        if (nlh->nlmsg_type == NLMSG_ERROR) { 
            // Do some error handling.       
            puts("eunetlink_recv: NLMSG_ERROR");  
        return 0;   
        } 
 
        /*处理有效的用户数据*/
        if (nlh->nlmsg_len > 0) 
        {
                char *str_buf = malloc(nlh->nlmsg_len); 
                memcpy(str_buf, NLMSG_DATA(nlh), nlh->nlmsg_len);
                
                str_buf[nlh->nlmsg_len - 1] = '\0';
                printf("Message received:%s\n",str_buf) ;
        
                free(str_buf);
        }
    }
 
    return 0;
}
#endif

#if 0
int tcp_connect(const char* host, const char* serv)
{
    int sockfd, n;
    struct addrinfo hints, *res, *cur;   

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((n = getaddrinfo(host, serv, &hints, &res)) != 0) 
    {
        printf("tcp_connect error for %s, %s: %s\n",
            host, serv, gai_strerror(n));
        return -1;
    }   

    for (cur = res; cur != NULL; cur = cur->ai_next) 
    {
        sockfd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if(sockfd < 0) 
        {
            continue;
        }

        if(connect(sockfd, cur->ai_addr, cur->ai_addrlen) == 0) 
        {
            break;
        }

        close(sockfd);
    }

    if(cur == NULL) 
    {
        printf("tcp_connect error for %s, %s: %s\n",
            host, serv, gai_strerror(n));
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);
    return(sockfd);
}
#endif

#include <sys/types.h>
#include <arpa/inet.h>
#include<netdb.h>
#include <stdio.h>
#include <string.h>

int tcp_listen(const char *host, const char *serv)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *cur;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    {
        printf("tcp_listen error for %s, %s: %s\n",
            host, serv, gai_strerror(n));
        return -1;
    }

    for (cur = res; cur != NULL; cur = cur->ai_next) 
    {
        listenfd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if(listenfd < 0) 
        {
            continue;
        }     

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if(bind(listenfd, cur->ai_addr, cur->ai_addrlen) == 0)
        {
            break;
        }

        close(listenfd);
    }

    if(cur == NULL) 
    {
        printf("tcp_listen error for %s, %s: %s\n",
            host, serv, gai_strerror(n));
        freeaddrinfo(res);
        return -1;
    } 

    listen(listenfd, 3);   
    freeaddrinfo(res);
    return(listenfd);
}

main()
{
    int fd;
    if ((fd = tcp_listen(NULL, "1044")) == -1 )
    {
        printf("wrong\n");
    }

    while(1)
    {
        sleep(2);
    }
}

/**************
测试结果
****************/

/***************
同类型函数:
***************/

