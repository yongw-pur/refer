/*************************
头文件
#include<sys/types.h>
#include<sys/socket.h>
int socket(int domain,int type,int protocol)
函数说明:建立一个新的socket，向系统注册通知系统建立一通信端口(套接字)
        domain指定使用何种的地址类型(https://blog.csdn.net/liuxingen/article/details/44995467)   
        PF_UNIX/PF_LOCAL/AF_UNIX/AF_LOCAL UNIX进程通信协议
        PF_INET/AF_INET Ipv4网络协议
        PF_INET6/AF_INET6 Ipv6 网络协议
        PF_IPX/AF_IPX IPX-Novell协议
        PF_NETLINK/AF_NETLINK 核心用户接口装置
        PF_X25/AF_X25 ITU-T X.25/ISO-8208 协议
        PF_AX25/AF_AX25 业余无线AX.25协议
        PF_ATMPVC/AF_ATMPVC 存取原始ATM PVCs
        PF_APPLETALK/AF_APPLETALK appletalk（DDP）协议
        PF_PACKET/AF_PACKET 初级封包接口
        type有下列几种数值
        SOCK_STREAM 提供双向连续且可信赖的数据流，即TCP。支持
        OOB 机制，在所有数据传送前必须使用connect()来建立连线状态。
        SOCK_DGRAM 使用不连续不可信赖的数据包连接
        SOCK_SEQPACKET 提供连续可信赖的数据包连接
        SOCK_RAW 提供原始网络协议存取
        SOCK_RDM 提供可信赖的数据包连接
        SOCK_PACKET 提供和网络驱动程序直接通信澹(过时)
        protocol参数情况:
        IPPROTO_TCP、IPPROTO_UDP、IPPROTO_STCP、IPPROTO_TIPC等，分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议
      type和protocol不可以随意组合，如SOCK_STREAM不可以跟IPPROTO_UDP组合。当第三个参数为0时，会自动选择第二个参数类型对应的默认协议
      socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP|ETH_P_ARP|ETH_P_ALL))
返回:成功则返回socket操作对象，失败返回-1

int bind(int sockfd,struct sockaddr * my_addr,int addrlen)
函数说明:设置给参数sockfd的socket一个名称,由参数my_addr指向一sockaddr结构
        sockaddr结构，对于不同的socket domain定义了一个通用的数据结构(sockaddr结构会因使用不同的socket domain而有不同结构定义)        
        struct sockaddr
        {
            unsigned short int sa_family;//socket调用时的domain参数，即AF_xxxx值
            char sa_data[14];
        };
        AF_INET domain:
        struct socketaddr_in
        {
            unsigned short int sin_family;//sa_family
            uint16_t sin_port;//使用的端口号
            struct in_addr sin_addr;
            unsigned char sin_zero[8];//未使用
        };
        struct in_addr
        {
            uint32_t s_addr;//IP 地址
        };
        addrlen为sockaddr的结构长度
        AF_PACKET domin:#include <sys/socket.h> #include <linux/if_packet.h> #include <net/ethernet.h> 
        struct sockaddr_ll 
        {
               unsigned short sll_family; //Always AF_PACKET 
               unsigned short sll_protocol; //Physical-layer protocol
               int sll_ifindex; //Interface number,0 匹配所有的网络接口卡
               unsigned short sll_hatype; //ARP hardware type
               unsigned char sll_pkttype; //Packet type
                 PACK_HOST                  包地址为本地主机地址。
                 PACK_BROADCAST    物理层广播包。
                 PACK_MULTICAST      发送到物理层多播地址的包。
                 PACK_OTHERHOST    发往其它在混杂模式下被设备捕获的主机的包。
                 PACK_OUTGOING        本地回环包；
               unsigned char sll_halen; //Length of address
               unsigned char sll_addr[8]; //Physical-layer address
         };
返回:成功则返回0，失败返回-1

int shutdown(int s,int how)
函数说明:终止参数s所指定的socket.
        参数how有下列几种情况:
        how=0 终止读取操作。
        how=1 终止传送操作
        how=2 终止读取及传送操作
返回:成功则返回0，失败返回-1//只会关闭连接，但是不会释放占用的文件描述符,后面还需要使用close关闭套接字

int recv(int s,void *buf,int len,unsigned int flags)
函数说明:收远端主机经指定的socket传来的数据，并把数据存到由参数buf 指向的内存空间，参数len为可接收数据的最大长度      
        flags一般设0。其他数值定义如下:
        MSG_OOB 接收以out-of-band 送出的数据。
        MSG_PEEK 返回来的数据并不会在系统内删除，如果再调用recv()会返回相同的数据内容。
        MSG_WAITALL强迫接收到len大小的数据后才能返回，除非有错误或信号产生。
        MSG_NOSIGNAL此操作不愿被SIGPIPE信号中断
返回:成功则返回接收到的字符数，失败返回-1

int recvfrom(int s,void *buf,int len,unsigned int flags ,struct sockaddr *from ,int *fromlen)
函数说明:接收远程主机经指定的socket传来的数据，并把数据存到由参数buf指向的内存空间，参数len为可接收数据的最大长度。参数flags一般设0
         参数from用来指定欲传送的网络地址,和bind参数一致，formlen为sockaddr结构的长度
返回:成功则返回接收到的字符数，失败则返回-1

int getsockopt(int s,int level,int optname,void* optval,socklen_t* optlen)
函数说明:获取socket状态，参数level代表欲设置的网络层，一般设成SOL_SOCKET以存取socket层，参数optname代表欲取得何种选项状态，而参数optval则指向欲保存结果的内存地址，参数optlen则为该空间的大小
        optname取值情况:       
        SO_DEBUG 打开或关闭排错模式
        SO_REUSEADDR 允许在bind过程中本地地址可重复使用
        SO_TYPE 返回socket形态。
        SO_ERROR 返回socket已发生的错误原因
        SO_DONTROUTE 送出的数据包不要利用路由设备来传输。
        SO_BROADCAST 使用广播方式传送
        SO_SNDBUF 设置送出的暂存区大小
        SO_RCVBUF 设置接收的暂存区大小
        SO_KEEPALIVE 定期确定连线是否已终止。
        SO_OOBINLINE 当接收到OOB 数据时会马上送至标准输入设备
        SO_LINGER 确保数据安全且可靠的传送出去
返回:成功则返回0，若有错误则返回-1

头文件:
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
unsigned long int inet_addr(const char *cp)
函数说明:将参数cp所指的网络地址字符串转换成32位二进制网络字节序的IPV4地址,网络地址字符串是以数字和点组成的字符串,例如:"163.13.132.68"
返回:成功则返回对应的网络二进制的数字，失败返回-1 //in_addr结构中的s_addr

int inet_aton(const char *cp,struct in_addr *inp)
函数说明:将参数cp所指的网络地址字符串转换成网络使用的二进制的数字，然后存于参数inp所指的in_addr结构中。
        结构in_addr定义如下(直接将字符串的高位放在低地址)
        struct in_addr
        {
            unsigned long int s_addr;
        };
返回:成功则返回非0值，失败则返回0

char *inet_ntoa(struct in_addr in)
函数说明:将参数in所指的网络二进制的数字转换成网络地址，然后将指向此网络地址字符串的指针返回//返回的是程序内的静态地址
返回:成功则返回字符串指针，失败则返回NULL

头文件:
#include <arpe/inet.h>
int inet_pton(int family, const char *strptr, void *addrptr)
函数说明:将点分十进制的ip地址转化为用于网络传输的数值格式
        family参数:AF_INET（ipv4）,AF_INET6（ipv6）
返回:若成功则为1，若输入不是有效的表达式则为0，若出错则为-1

const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
函数说明:将数值格式转化为点分十进制的ip地址格式
        从数值格式addrptr转换到表达格式strptr,len参数是目标存储单元的大小，以免该函数溢出其调用者的缓冲区
        在<netinet/in.h>头文件中有如下定义：
        #define INET_ADDRSTRLEN   16
        #define INET6_ADDRSTRLEN  46
        const u_char *p = (const u_char *) addrptr;
        snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

        in_addr_t 一般为 32位的unsigned int，其字节顺序为网络顺序（network byte ordered)，即该无符号整数采用大端字节序澹(高位放低地址)
        192.168.3.144记为0x9003a8c0,其中 c0为192 ,a8 为 168, 03 为 3 , 90 为 144

        #define IPV4(a,b,c,d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))
        unsigned int value=IPV4(127,0,0,1);    //这里是已逗号分开。
        in_addr_t ip;
        memcpy(&ip,&value,sizeof(value));
返回:若成功则为指向结构的指针，若出错则为NULL(字节序不对应，就会出现颠倒情况.一台机器上一般不会，只有一个结构默认使用了字节序，然后转换出现问题)

头文件:
#include<netinet/in.h>
unsigned long int ntohl(unsigned long int net)
函数说明:将参数指定的32位网络字节序net转换成主机字符顺序
返回:返回对应的主机字符顺序

unsigned short int ntohs(unsigned short int net)
函数说明:将参数指定的16位网络字节序net转换成主机字符顺序

头文件
#include <netdb.h>
struct protoent *getprotobyname(const char *name)
函数说明:根据名称返回协议相关信息
        struct protoent
        {
          char *p_name;         //Official protocol name.
          char **p_aliases;     //Alias list.
          int p_proto;          //Protocol number.
        };
返回:成功返回protoent结构，否则返回NULL 同getprotobynumber(int proto);

struct protoent *getprotoent(void)
函数说明:从/etc/protocols中读取条目
返回:成功放回protoent结构，失败或到最后返回NULL

void setprotoent(int stayopen)
函数说明:打开/etc/services,后面使用endprotoent关闭
         如果参数stayopen值为1，则接下来的getprotobyname()或getprotobynumber()将不会自动关闭文件


struct hostent *gethostbyname(const char *hostname)
函数说明:返回对应于给定主机名hostent结构的指针，结构体包含主机名字和地址信息
        struct hostent 
        {
            char  *h_name; //official name of host 主机的规范名。例如www.google.com的规范名其实是www.l.google.com
            char **h_aliases; //alias list 表示的是主机的别名.www.google.com就是google他自己的别名,可能有好几个别名
            int    h_addrtype;//host address type  表示的是主机ip地址的类型，ipv4(AF_INET)，还是pv6(AF_INET6)
            int    h_length; //length of address 表示的是主机ip地址的长度
            char **h_addr_list;//list of addresses 表示的是主机的ip地址，注意，这个是以网络字节序存储的。千万不要直接用printf带%s参数来，使用inet_ntop()//inet_ntoa(*(struct in_addr*)hp->h_addr_list[i])
        }
返回:成功返回指向hostent结构的指针，否则，返回一个空指针

struct servent *getservbyname(const char *servname, const char *protoname)
函数说明:根据给定名字查找相应服务，即：返回对应于给定服务名和协议名的相关服务信息(例如：端口号)
        struct servent
        {
          char   *s_name;  //fficial service name 
          char  **s_aliases; //alias list
          int     s-port; //port number, network-byte order 
          char   *s_proto;  //protocol to use 
        };
        getservbyname("domain", "udp"); //DNS using UDP
        getservbyname("ftp", "tcp");    //TP using TCP
        getservbyname("ftp", NULL);     //TP using TCP

struct servent *getservbyport (int port, const char *protoname)
函数说明:用于给定端口号和可选协议查找相应服务,port参数的值必须为网络字节序
        getservbyport (htons (53), "udp"); //DNS using UDP 
        getservbyport (htons (21), "tcp"); //FTP using TCP 
        getservbyport (htons (21), NULL);  //FTP using TCP 

struct servent *getservent(void)
函数说明:从 _PATH_SERVICES /etc/services中读取下一个条目
返回:成功放回servent结构，失败或到最后返回NULL

void setservent(int stayopen)
函数说明:打开/etc/services,后面使用endservent关闭
         如果参数stayopen值为1，则接下来的getservbyname()或getservbyport()将不会自动关闭文件
**************************/
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include<sys/types.h>
#include <arpa/inet.h> /*htonl htons ntohs */
#include <sys/ioctl.h>
#include <net/if.h>


static void printproto(struct protoent *proto)
{
	char **p = NULL;
	
	printf("protocol: %s\n", proto->p_name);
	
	for(p = proto->p_aliases; *p; p++)
	{
		printf("alias: %s\n", *p);
	}
	
	printf("protocol: %d\n", proto->p_proto);
}

static void printserv(struct servent *serv)
{
	char **p = NULL;
	
	printf("service name: %s\n", serv->s_name);
	
	for(p = serv->s_aliases; *p != NULL; p++)
	{
		printf("aliase: %s\n", *p);
	}
	
	printf("port number: %d\n", ntohs(serv->s_port));	// Note: the port here is in network byte order. use ntohs(), not ntohl(), I don't know why.
	printf("protocol: %s\n", serv->s_proto);
}

int main()
{
    int fd;
    char dev_name[] = "eth0";
    struct ifreq ifr;
    struct sockaddr_ll sll;

     memset(&ifr, 0, sizeof(ifr));
     memset(&sll, 0, sizeof(sll));
    
    fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  
    strncpy(ifr.ifr_name, dev_name, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1)
    {
        fprintf(stderr, "%s: ioctl failed.\n", __func__);
        return -1;
    }

    if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0)
    {
      close(fd);
      return -1;
    }
    
    if(ifr.ifr_flags & IFF_RUNNING)
    {
        printf("eth link up\n");
    }
    else
    {
        printf("eth link down\n");
    }
  
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl(fd, SIOCSIFFLAGS, &ifr) < 0)
    {
      return -1;
    }
    
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);
    bind(fd, (struct sockaddr *)&sll, sizeof(sll));

    
    struct servent *serv = NULL;
    setservent(1);
    printf("Servent:\n");
    while ((serv = getservent()) != NULL)
    {
        printserv(serv);
        printf("\n");
    }
    endservent();

    
	struct protoent *proto = NULL;
	setprotoent(1);
    printf("protoent:\n");
	while ((proto = getprotoent()) != NULL)
	{
		printproto(proto);
		printf("\n");
	}
	endprotoent();
}

/**************
测试结果
****************/

/***************
同类型函数:
int listen(int s,int backlog)//等待参数s 的socket连线。参数backlog指定同时能处理的最大连接要求，如果连接数目达此上限则client端将收到ECONNREFUSED的错误
      listen并未开始接收连线，只是设置socket为listen模式，真正接收client端连线的是accept
      listen只适用SOCK_STREAM或SOCK_SEQPACKET的socket类型。如果socket为AF_INET则参数backlog 最大值可设至128
int connect (int sockfd,struct sockaddr *serv_addr,int addrlen)//参数sockfd的socket连至参数serv_addr指定的网络地址
int accept(int s,struct sockaddr * addr,int * addrlen)//来接受参数s的socket连线。参数s的socket必需先经bind()、listen()函数处理过
      当有连线进来时accept()会返回一个新的socket处理代码，往后的数据传送与读取就是经由新的socket处理，而原来参数s的socket能继续使用accept()来接受新的连线要求
      连线成功时，参数addr所指的结构会被系统填入远程主机的地址数据
      成功则返回新的socket处理代码，失败返回-1
struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family)//有一个二进制的IP地址找到相应的主机名
      参数addr实际上不是char *类型，而是一个指向存放IPv4地址的某个in_addr结构的指针；len参数是这个结构的大小:地域IPv4地址为4，family参数为AF_INET
unsigned short int htons(unsigned short int net)//16位主机序转换为网络字节序
unsigned long int htonl(unsigned long int net)//32位主机序转换为网络字节序
int send(int s,const void * msg,int len,unsigned int falgs)//数据由指定的socket 传给对方主机。参数s为已建立好连接的socket。参数msg指向欲连线的数据内容，参数len则为数据长度      
    参数flags一般设0，其他数值定义如下MSG_OOB 传送的数据以out-of-band 送出,MSG_DONTROUTE 取消路由表查询,MSG_DONTWAIT 设置为不可阻断运作,MSG_NOSIGNAL 此动作不愿被SIGPIPE 信号中断
int sendto ( int s , const void * msg, int len, unsigned int flags, const struct sockaddr * to , int tolen )//将数据由指定的socket传给对方主机。参数s为已建好连线的socket,如果利用UDP协议则不需经过连线操作
    参数msg指向欲连线的数据内容，参数flags一般设0，参数to用来指定欲传送的网络地址，参数tolen为sockaddr的长度
int setsockopt(int s,int level,int optname,const void * optval,,socklen_toptlen)//设置参数s所指定的socket状态,参考get
***************/

