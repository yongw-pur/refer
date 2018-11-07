/*************************
ͷ�ļ�
#include<sys/types.h>
#include<sys/socket.h>
int socket(int domain,int type,int protocol)
����˵��:����һ���µ�socket����ϵͳע��֪ͨϵͳ����һͨ�Ŷ˿�(�׽���)
        domainָ��ʹ�ú��ֵĵ�ַ����(https://blog.csdn.net/liuxingen/article/details/44995467)   
        PF_UNIX/PF_LOCAL/AF_UNIX/AF_LOCAL UNIX����ͨ��Э��
        PF_INET/AF_INET Ipv4����Э��
        PF_INET6/AF_INET6 Ipv6 ����Э��
        PF_IPX/AF_IPX IPX-NovellЭ��
        PF_NETLINK/AF_NETLINK �����û��ӿ�װ��
        PF_X25/AF_X25 ITU-T X.25/ISO-8208 Э��
        PF_AX25/AF_AX25 ҵ������AX.25Э��
        PF_ATMPVC/AF_ATMPVC ��ȡԭʼATM PVCs
        PF_APPLETALK/AF_APPLETALK appletalk��DDP��Э��
        PF_PACKET/AF_PACKET ��������ӿ�
        type�����м�����ֵ
        SOCK_STREAM �ṩ˫�������ҿ�����������������TCP��֧��
        OOB ���ƣ����������ݴ���ǰ����ʹ��connect()����������״̬��
        SOCK_DGRAM ʹ�ò������������������ݰ�����
        SOCK_SEQPACKET �ṩ���������������ݰ�����
        SOCK_RAW �ṩԭʼ����Э���ȡ
        SOCK_RDM �ṩ�����������ݰ�����
        SOCK_PACKET �ṩ��������������ֱ��ͨ���(��ʱ)
        protocol�������:
        IPPROTO_TCP��IPPROTO_UDP��IPPROTO_STCP��IPPROTO_TIPC�ȣ��ֱ��ӦTCP����Э�顢UDP����Э�顢STCP����Э�顢TIPC����Э��
      type��protocol������������ϣ���SOCK_STREAM�����Ը�IPPROTO_UDP��ϡ�������������Ϊ0ʱ�����Զ�ѡ��ڶ����������Ͷ�Ӧ��Ĭ��Э��
      socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP|ETH_P_ARP|ETH_P_ALL))
����:�ɹ��򷵻�socket��������ʧ�ܷ���-1

int bind(int sockfd,struct sockaddr * my_addr,int addrlen)
����˵��:���ø�����sockfd��socketһ������,�ɲ���my_addrָ��һsockaddr�ṹ
        sockaddr�ṹ�����ڲ�ͬ��socket domain������һ��ͨ�õ����ݽṹ(sockaddr�ṹ����ʹ�ò�ͬ��socket domain���в�ͬ�ṹ����)        
        struct sockaddr
        {
            unsigned short int sa_family;//socket����ʱ��domain��������AF_xxxxֵ
            char sa_data[14];
        };
        AF_INET domain:
        struct socketaddr_in
        {
            unsigned short int sin_family;//sa_family
            uint16_t sin_port;//ʹ�õĶ˿ں�
            struct in_addr sin_addr;
            unsigned char sin_zero[8];//δʹ��
        };
        struct in_addr
        {
            uint32_t s_addr;//IP ��ַ
        };
        addrlenΪsockaddr�Ľṹ����
        AF_PACKET domin:#include <sys/socket.h> #include <linux/if_packet.h> #include <net/ethernet.h> 
        struct sockaddr_ll 
        {
               unsigned short sll_family; //Always AF_PACKET 
               unsigned short sll_protocol; //Physical-layer protocol
               int sll_ifindex; //Interface number,0 ƥ�����е�����ӿڿ�
               unsigned short sll_hatype; //ARP hardware type
               unsigned char sll_pkttype; //Packet type
                 PACK_HOST                  ����ַΪ����������ַ��
                 PACK_BROADCAST    �����㲥����
                 PACK_MULTICAST      ���͵������ಥ��ַ�İ���
                 PACK_OTHERHOST    ���������ڻ���ģʽ�±��豸����������İ���
                 PACK_OUTGOING        ���ػػ�����
               unsigned char sll_halen; //Length of address
               unsigned char sll_addr[8]; //Physical-layer address
         };
����:�ɹ��򷵻�0��ʧ�ܷ���-1

int shutdown(int s,int how)
����˵��:��ֹ����s��ָ����socket.
        ����how�����м������:
        how=0 ��ֹ��ȡ������
        how=1 ��ֹ���Ͳ���
        how=2 ��ֹ��ȡ�����Ͳ���
����:�ɹ��򷵻�0��ʧ�ܷ���-1//ֻ��ر����ӣ����ǲ����ͷ�ռ�õ��ļ�������,���滹��Ҫʹ��close�ر��׽���

int recv(int s,void *buf,int len,unsigned int flags)
����˵��:��Զ��������ָ����socket���������ݣ��������ݴ浽�ɲ���buf ָ����ڴ�ռ䣬����lenΪ�ɽ������ݵ���󳤶�      
        flagsһ����0��������ֵ��������:
        MSG_OOB ������out-of-band �ͳ������ݡ�
        MSG_PEEK �����������ݲ�������ϵͳ��ɾ��������ٵ���recv()�᷵����ͬ���������ݡ�
        MSG_WAITALLǿ�Ƚ��յ�len��С�����ݺ���ܷ��أ������д�����źŲ�����
        MSG_NOSIGNAL�˲�����Ը��SIGPIPE�ź��ж�
����:�ɹ��򷵻ؽ��յ����ַ�����ʧ�ܷ���-1

int recvfrom(int s,void *buf,int len,unsigned int flags ,struct sockaddr *from ,int *fromlen)
����˵��:����Զ��������ָ����socket���������ݣ��������ݴ浽�ɲ���bufָ����ڴ�ռ䣬����lenΪ�ɽ������ݵ���󳤶ȡ�����flagsһ����0
         ����from����ָ�������͵������ַ,��bind����һ�£�formlenΪsockaddr�ṹ�ĳ���
����:�ɹ��򷵻ؽ��յ����ַ�����ʧ���򷵻�-1

int getsockopt(int s,int level,int optname,void* optval,socklen_t* optlen)
����˵��:��ȡsocket״̬������level���������õ�����㣬һ�����SOL_SOCKET�Դ�ȡsocket�㣬����optname������ȡ�ú���ѡ��״̬��������optval��ָ�������������ڴ��ַ������optlen��Ϊ�ÿռ�Ĵ�С
        optnameȡֵ���:       
        SO_DEBUG �򿪻�ر��Ŵ�ģʽ
        SO_REUSEADDR ������bind�����б��ص�ַ���ظ�ʹ��
        SO_TYPE ����socket��̬��
        SO_ERROR ����socket�ѷ����Ĵ���ԭ��
        SO_DONTROUTE �ͳ������ݰ���Ҫ����·���豸�����䡣
        SO_BROADCAST ʹ�ù㲥��ʽ����
        SO_SNDBUF �����ͳ����ݴ�����С
        SO_RCVBUF ���ý��յ��ݴ�����С
        SO_KEEPALIVE ����ȷ�������Ƿ�����ֹ��
        SO_OOBINLINE �����յ�OOB ����ʱ������������׼�����豸
        SO_LINGER ȷ�����ݰ�ȫ�ҿɿ��Ĵ��ͳ�ȥ
����:�ɹ��򷵻�0�����д����򷵻�-1

ͷ�ļ�:
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
unsigned long int inet_addr(const char *cp)
����˵��:������cp��ָ�������ַ�ַ���ת����32λ�����������ֽ����IPV4��ַ,�����ַ�ַ����������ֺ͵���ɵ��ַ���,����:"163.13.132.68"
����:�ɹ��򷵻ض�Ӧ����������Ƶ����֣�ʧ�ܷ���-1 //in_addr�ṹ�е�s_addr

int inet_aton(const char *cp,struct in_addr *inp)
����˵��:������cp��ָ�������ַ�ַ���ת��������ʹ�õĶ����Ƶ����֣�Ȼ����ڲ���inp��ָ��in_addr�ṹ�С�
        �ṹin_addr��������(ֱ�ӽ��ַ����ĸ�λ���ڵ͵�ַ)
        struct in_addr
        {
            unsigned long int s_addr;
        };
����:�ɹ��򷵻ط�0ֵ��ʧ���򷵻�0

char *inet_ntoa(struct in_addr in)
����˵��:������in��ָ����������Ƶ�����ת���������ַ��Ȼ��ָ��������ַ�ַ�����ָ�뷵��//���ص��ǳ����ڵľ�̬��ַ
����:�ɹ��򷵻��ַ���ָ�룬ʧ���򷵻�NULL

ͷ�ļ�:
#include <arpe/inet.h>
int inet_pton(int family, const char *strptr, void *addrptr)
����˵��:�����ʮ���Ƶ�ip��ַת��Ϊ�������紫�����ֵ��ʽ
        family����:AF_INET��ipv4��,AF_INET6��ipv6��
����:���ɹ���Ϊ1�������벻����Ч�ı��ʽ��Ϊ0����������Ϊ-1

const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
����˵��:����ֵ��ʽת��Ϊ���ʮ���Ƶ�ip��ַ��ʽ
        ����ֵ��ʽaddrptrת��������ʽstrptr,len������Ŀ��洢��Ԫ�Ĵ�С������ú������������ߵĻ�����
        ��<netinet/in.h>ͷ�ļ��������¶��壺
        #define INET_ADDRSTRLEN   16
        #define INET6_ADDRSTRLEN  46
        const u_char *p = (const u_char *) addrptr;
        snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

        in_addr_t һ��Ϊ 32λ��unsigned int�����ֽ�˳��Ϊ����˳��network byte ordered)�������޷����������ô���ֽ����(��λ�ŵ͵�ַ)
        192.168.3.144��Ϊ0x9003a8c0,���� c0Ϊ192 ,a8 Ϊ 168, 03 Ϊ 3 , 90 Ϊ 144

        #define IPV4(a,b,c,d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))
        unsigned int value=IPV4(127,0,0,1);    //�������Ѷ��ŷֿ���
        in_addr_t ip;
        memcpy(&ip,&value,sizeof(value));
����:���ɹ���Ϊָ��ṹ��ָ�룬��������ΪNULL(�ֽ��򲻶�Ӧ���ͻ���ֵߵ����.һ̨������һ�㲻�ᣬֻ��һ���ṹĬ��ʹ�����ֽ���Ȼ��ת����������)

ͷ�ļ�:
#include<netinet/in.h>
unsigned long int ntohl(unsigned long int net)
����˵��:������ָ����32λ�����ֽ���netת���������ַ�˳��
����:���ض�Ӧ�������ַ�˳��

unsigned short int ntohs(unsigned short int net)
����˵��:������ָ����16λ�����ֽ���netת���������ַ�˳��

ͷ�ļ�
#include <netdb.h>
struct protoent *getprotobyname(const char *name)
����˵��:�������Ʒ���Э�������Ϣ
        struct protoent
        {
          char *p_name;         //Official protocol name.
          char **p_aliases;     //Alias list.
          int p_proto;          //Protocol number.
        };
����:�ɹ�����protoent�ṹ�����򷵻�NULL ͬgetprotobynumber(int proto);

struct protoent *getprotoent(void)
����˵��:��/etc/protocols�ж�ȡ��Ŀ
����:�ɹ��Ż�protoent�ṹ��ʧ�ܻ���󷵻�NULL

void setprotoent(int stayopen)
����˵��:��/etc/services,����ʹ��endprotoent�ر�
         �������stayopenֵΪ1�����������getprotobyname()��getprotobynumber()�������Զ��ر��ļ�


struct hostent *gethostbyname(const char *hostname)
����˵��:���ض�Ӧ�ڸ���������hostent�ṹ��ָ�룬�ṹ������������ֺ͵�ַ��Ϣ
        struct hostent 
        {
            char  *h_name; //official name of host �����Ĺ淶��������www.google.com�Ĺ淶����ʵ��www.l.google.com
            char **h_aliases; //alias list ��ʾ���������ı���.www.google.com����google���Լ��ı���,�����кü�������
            int    h_addrtype;//host address type  ��ʾ��������ip��ַ�����ͣ�ipv4(AF_INET)������pv6(AF_INET6)
            int    h_length; //length of address ��ʾ��������ip��ַ�ĳ���
            char **h_addr_list;//list of addresses ��ʾ����������ip��ַ��ע�⣬������������ֽ���洢�ġ�ǧ��Ҫֱ����printf��%s��������ʹ��inet_ntop()//inet_ntoa(*(struct in_addr*)hp->h_addr_list[i])
        }
����:�ɹ�����ָ��hostent�ṹ��ָ�룬���򣬷���һ����ָ��

struct servent *getservbyname(const char *servname, const char *protoname)
����˵��:���ݸ������ֲ�����Ӧ���񣬼������ض�Ӧ�ڸ�����������Э��������ط�����Ϣ(���磺�˿ں�)
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
����˵��:���ڸ����˿ںźͿ�ѡЭ�������Ӧ����,port������ֵ����Ϊ�����ֽ���
        getservbyport (htons (53), "udp"); //DNS using UDP 
        getservbyport (htons (21), "tcp"); //FTP using TCP 
        getservbyport (htons (21), NULL);  //FTP using TCP 

struct servent *getservent(void)
����˵��:�� _PATH_SERVICES /etc/services�ж�ȡ��һ����Ŀ
����:�ɹ��Ż�servent�ṹ��ʧ�ܻ���󷵻�NULL

void setservent(int stayopen)
����˵��:��/etc/services,����ʹ��endservent�ر�
         �������stayopenֵΪ1�����������getservbyname()��getservbyport()�������Զ��ر��ļ�
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
���Խ��
****************/

/***************
ͬ���ͺ���:
int listen(int s,int backlog)//�ȴ�����s ��socket���ߡ�����backlogָ��ͬʱ�ܴ�����������Ҫ�����������Ŀ���������client�˽��յ�ECONNREFUSED�Ĵ���
      listen��δ��ʼ�������ߣ�ֻ������socketΪlistenģʽ����������client�����ߵ���accept
      listenֻ����SOCK_STREAM��SOCK_SEQPACKET��socket���͡����socketΪAF_INET�����backlog ���ֵ������128
int connect (int sockfd,struct sockaddr *serv_addr,int addrlen)//����sockfd��socket��������serv_addrָ���������ַ
int accept(int s,struct sockaddr * addr,int * addrlen)//�����ܲ���s��socket���ߡ�����s��socket�����Ⱦ�bind()��listen()���������
      �������߽���ʱaccept()�᷵��һ���µ�socket������룬��������ݴ������ȡ���Ǿ����µ�socket������ԭ������s��socket�ܼ���ʹ��accept()�������µ�����Ҫ��
      ���߳ɹ�ʱ������addr��ָ�Ľṹ�ᱻϵͳ����Զ�������ĵ�ַ����
      �ɹ��򷵻��µ�socket������룬ʧ�ܷ���-1
struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family)//��һ�������Ƶ�IP��ַ�ҵ���Ӧ��������
      ����addrʵ���ϲ���char *���ͣ�����һ��ָ����IPv4��ַ��ĳ��in_addr�ṹ��ָ�룻len����������ṹ�Ĵ�С:����IPv4��ַΪ4��family����ΪAF_INET
unsigned short int htons(unsigned short int net)//16λ������ת��Ϊ�����ֽ���
unsigned long int htonl(unsigned long int net)//32λ������ת��Ϊ�����ֽ���
int send(int s,const void * msg,int len,unsigned int falgs)//������ָ����socket �����Է�����������sΪ�ѽ��������ӵ�socket������msgָ�������ߵ��������ݣ�����len��Ϊ���ݳ���      
    ����flagsһ����0��������ֵ��������MSG_OOB ���͵�������out-of-band �ͳ�,MSG_DONTROUTE ȡ��·�ɱ��ѯ,MSG_DONTWAIT ����Ϊ�����������,MSG_NOSIGNAL �˶�����Ը��SIGPIPE �ź��ж�
int sendto ( int s , const void * msg, int len, unsigned int flags, const struct sockaddr * to , int tolen )//��������ָ����socket�����Է�����������sΪ�ѽ������ߵ�socket,�������UDPЭ�����辭�����߲���
    ����msgָ�������ߵ��������ݣ�����flagsһ����0������to����ָ�������͵������ַ������tolenΪsockaddr�ĳ���
int setsockopt(int s,int level,int optname,const void * optval,,socklen_toptlen)//���ò���s��ָ����socket״̬,�ο�get
***************/

