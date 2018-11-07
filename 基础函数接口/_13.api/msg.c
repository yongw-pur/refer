/*************************
ͷ�ļ�
#include<netdb.h>
int getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
����˵��:hostname:һ�����������ߵ�ַ��(IPv4�ĵ��ʮ���ƴ�����IPv6��16���ƴ�)
         service��һ������������10���ƶ˿ں�������
         hints:������һ����ָ�룬Ҳ������һ��ָ��ĳ��addrinfo�ṹ��ָ�룬������������ṹ����������������ص���Ϣ���͵İ�ʾ
                 ����:���ָ���ķ����֧��TCPҲ֧��UDP����ô�����߿��԰�hints�ṹ�е�ai_socktype��Ա���ó�SOCK_DGRAMʹ�÷��صĽ��������������ݱ��׽ӿڵ���Ϣ��
         resultָ��:��������һ��ָ��addrinfo�ṹ�����ָ��
    struct addrinfo
    {
      int ai_flags;	//Input flags
        AI_PASSIVE	�׽��ֵ�ַ�����ڵ���bind ����;���ڵ���λNULL���Ҵ˱�־��λ���򷵻صĵ�ַ����ͨ���ַ;����ڵ���NULL���Ҵ˱�־����λ���򷵻صĵ�ַ���ǻػ���ַ��
        AI_CANONNAME	���ع淶����
        AI_NUMERICHOST	���ݸ�getaddrinfo������nodename���������������ַ�����
        AI_ALL	If this bit is set, a request is made for IPv6 addresses and IPv4 addresses with AI_V4MAPPED.
        AI_ADDRCONFIG	ֻ��������ȫ�ֵ�ַ��getaddrinfo�Ż������ IPv6��IPv4���ص�ַ������Ϊ����Ч��ȫ�ֵ�ַ��
        AI_V4MA PPED	�����IPv6��ַ��getaddrinfo����ʧ�ܣ����IPv4��ַ�������Ʒ���������Щ��ַ��ת��ΪIPv4ӳ��IPv6��ַ��ʽ��
        AI_NON_AUTHORITATIVE	��ַ��Ϣ�������Է���Ȩ�����ռ��ṩ��
        AI_SECURE	��ַ��Ϣ���԰�ȫ�ŵ���
        AI_RETURN_PREFERRED_NAMES	��ַ��Ϣ�������û�����ѡ���ơ�
        AI_FQDN	getaddrinfo�������������ս���Ϊ����ȫ�޶������� ��ȫ�޶�������ai_canonname��Ա�з��ء�
        ����AI_CANONNAMEλ��ǲ�ͬ�����߷�����DNS��ע��Ĺ淶���ƣ������ƿ�����ƽ�����ƽ���Ϊ����ȫ�޶�������ͬ��
        ֻ������AI_FQDN��AI_CANONNAMEλ�е�һ��,���EAI_BADFLAGSͬʱ������������־��getaddrinfo������ʧ�ܡ�
        AI_FILESERVER	�����ռ��ṩ������ʾ���ڲ�ѯ�������������ļ���������ʹ�á� �����ռ��ṩ������Ժ��Դ���ʾ��
      int ai_family;//Protocol family for socket: AF_INET(IPv4),AF_INET6(IPv6),AF_UNSPEC(Э���޹�)
      int ai_socktype;//Socket type:SOCK_STREAM(������,TCP),SOCK_DGRAM(���ݱ�,UDP)
      int ai_protocol;//Protocol for socket:IPPROTO_TCP�������Э�飨TCP��,IPPROTO_UDP�û����ݱ�Э�飨UDP��ai_protocolָ����ֵ0��������߲�ϣ��ָ��Э�飬�����ṩ�߽�ѡ��Ҫʹ�õ�ai_protocol
      socklen_t ai_addrlen;	//Length of socket address. ָ��Ļ������ĳ��ȣ����ֽ�Ϊ��λ��
      struct sockaddr *ai_addr;	//Socket address for socket.ָ�� sockaddr �ṹ��ָ�롣ÿ�����ص�addrinfo�ṹ�е�ai_addr��Աָ��һ�������׽��ֵ�ַ�ṹ��ÿ�����ص�addrinfo�ṹ�ĳ��ȣ����ֽ�Ϊ��λ����ai_addrlen��Ա��ָ��
      char *ai_canonname;//Canonical name for service location. �����Ĺ淶����
      struct addrinfo *ai_next;	//Pointer to next in list
     }; 
     struct sockaddr 
     {
        ushort  sa_family;
        char    sa_data[14];
     };
1.�����node���������ĵ�ַ�ж������ô�������������ַ�ص�ÿ����ַ������һ����Ӧ�Ľṹ��
2.���service����ָ���ķ���֧�ֶ���׽ӿ����ͣ���ôÿ���׽ӿ����Ͷ����ܷ���һ����Ӧ�Ľṹ������ȡ����hints�ṹ��ai_socktype��Ա
������ǰ���������ֱ��ǽڵ����ͷ��������ڵ�����������������Ҳ�����ǵ�ַ��(IPv4�ĵ��ʮ��������ʾ��IPv6��ʮ���������ִ�)��������������ʮ���ƵĶ˿ںţ�Ҳ�������Ѷ���ķ������ƣ���ftp��http��

ͨ�����������ڵ���getaddrinfo֮ǰ��ai_flags����AI_PASSIVE������bind��������nodenameͨ��������ΪNULL������ͨ���ַ[::]

int recvmsg(int s,struct msghdr *msg,unsigned int flags)
����˵��:����Զ��������ָ����socket���������ݡ�����sΪ�ѽ��������ߵ�socket���������UDPЭ�����辭�����߲���������msgָ�������ߵ����ݽṹ���ݣ�����flagsһ����0
        struct msghdr
        {
            void *msg_name; //Address to send to /receive from:�����ݰ���Ŀ�ĵ�ַ�������ָ��struct sockaddr_in,���ں˷�����ʱ��ָ��struct sockaddr_nl
            socklen_t msg_namelen; //Length of addres data
            strcut iovec * msg_iov; //Vector of data to send/receive into
            size_t msg_iovlen; //Number of elements in the vector
            void * msg_control; //Ancillary dat
            size_t msg_controllen; //Ancillary data buffer length
            int msg_flags; //Flags on received message
        };
        msg_name �� msg_namelen ��������Ա�����׽���δ���ӵĳ���:��δ���� UDP �׽���,�������� recvfrom �� sendto �ĵ�����͵���������
        msg_iov �� msg_iovlen��������Աָ�������������������飨��iovec�ṹ���飩
        msg_control �� msg_controllen ��������Աָ����ѡ�ĸ������ݵ�λ�úʹ�С
        ֻ��recvmsgʹ��msg_flags��Ա��recvmsg������ʱ��flags������������msg_flags��Ա�������ں�ʹ����ֵ�������մ������

        ������Ϣͷ��
        struct cmsghdr 
        {
             socklen_t cmsg_len; //�������ݵ��ֽڼ�����������ṹͷ�ĳߴ硣���ֵ����CMSG_LEN()������
             int       cmsg_level; //������ԭʼ��Э�鼶��(���磬SOL_SOCKET)
             int       cmsg_type;  //�����˿�����Ϣ����(���磬SCM_RIGHTS:�������ݶ�����һ���ļ�������)
        };

struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *msgh);//����һ��ָ�������ݻ������ڵĵ�һ�����������struct cmsghdrָ��
        ���������msghdr�ĳ�Աmsg_control��msg_controllen��ȷ���ڻ��������Ƿ���ڸ�������Ȼ��������㷵�ص�ָ�롣
        ��������ڸ������ݶ����򷵻ص�ָ��ֵΪNULL���������ָ���ָ����ڵĵ�һ��struct cmsghdr
struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh, struct cmsghdr *cmsg);//
        ������һ���������ݶ����struct cmsghdrָ�롣����������������������
        ָ��struct msghdr�ṹ��ָ��
        ָ��ǰstruct cmsghdr��ָ��
        ���û����һ���������ݶ��������ͻ᷵��NULL
size_t CMSG_ALIGN(size_t length);//ָ��һ���ֽڳ�����Ϊ���룬���������һ���µĳ��ȣ�����³��Ȱ���Ϊ��ά����������Ҫ�Ķ��������ֽ�
size_t CMSG_SPACE(size_t length);//���㸽�������Լ���ͷ��������ܿհ�
size_t CMSG_LEN(size_t length);//��������ϣ�������ڸ������ݻ������еĶ���ߴ���Ϊ�������
        ����cmsghdrͷ�ṹ��������Ҫ������ַ����ֽڳ��ȣ���������cmsghdr�����cmsg_len��Ա��CMSG_LEN()ֵ�����������ܵĽ�β������ַ�
void *CMSG_DATA(struct cmsghdr *cmsg);//���ص�ָ��ֵָ�������ͷ���Լ�����ֽ�֮��ĸ������ݵĵ�һ���ֽ�(�������)

��ȡcmsghdr����
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

����cmsghdr����
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
fd��Ҫ�����Ͻ��ж�����д���ļ�������fd,vector�Ƕ���д���õ�I/O����,count��Ҫʹ�õ�����Ԫ�ظ���


nlmsghdr����:
NLMSG_SPACE(MAX_PAYLOAD)�ú����ڷ��ز�С��MAX_PAYLOAD��4�ֽڶ������С����ֵ��һ���������ڴ�ϵͳ����ռ���ָ����������ڴ��ֽ���
NLMSG_LENGTH(len)��Ϣ���غ���Ϣͷ���������ܳ��ȡ�
NLMSG_DATA(nlh)����Netlink��Ϣ�����ݲ��ֵ��׵�ַ

len = recvmsg(nl_sock, &msg, 0);
for (nh = (struct nlmsghdr *)buf; NLMSG_OK(nh, len); nh = NLMSG_NEXT (nh, len))

struct msghdr msg; 
memset(&msg, 0, sizeof(msg));
msg.msg_name = (void *)&(nladdr);
msg.msg_namelen = sizeof(nladdr);
char buffer[] = "An example message";
struct nlmsghdr nlhdr;
nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));
strcpy(NLMSG_DATA(nlhdr),buffer);//�����ݴ������Ϣͷָ������ݵ�ַ
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
    char buffer[65536]; /*��ʱbuffer�����ڽ����ں˷�����������*/  
    int len;       
 
    /*����������Ϣ�ṹ��*/ 
    msg.msg_name = (void *)&(nladdr);  /*�趨���յķ���Դ��ַ*/   
    msg.msg_namelen = sizeof(nladdr);  
 
    /*�趨��ʱ����*/
    iov[0].iov_base = (void *)buffer; 
    iov[0].iov_len = sizeof(buffer);
    msg.msg_iov = iov;                    
    msg.msg_iovlen = sizeof(iov)/sizeof(iov[0]);  /*��������ʱ����*/
    
    len = recvmsg(sock, &msg, 0);  /*�����ȴ�������(�����ر��趨��socket��������ʽ����)*/
    if (len < 0) { 
        printf("recvmsg error: %d", len);     
        return len; 
    }       
 
    /*�������յ�����Ϣ���ݣ����д���
        NLMSG_OK���ж������ǲ����Ѿ�����
        NLMSG_NEXT ���޸�nlh��len��ֵ��ʹָ֮��buffer�е���һ��netlink��Ϣ
       */     
    for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, len); nlh = NLMSG_NEXT(nlh, len)) {  
        if (nlh->nlmsg_type == NLMSG_ERROR) { 
            // Do some error handling.       
            puts("eunetlink_recv: NLMSG_ERROR");  
        return 0;   
        } 
 
        /*������Ч���û�����*/
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
���Խ��
****************/

/***************
ͬ���ͺ���:
***************/

