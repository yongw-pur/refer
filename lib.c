/* lib.c - collections of some functions
 *   NOTICE: it is not surprised to see the
 *     same complishment of functions
 *
 * AUTHER: SeanW
 * Copyright: None
 * Original date: 2017.08.06
 *
 * Possible future improvements:
 *        -Give some examples for each function
 *        -Think twice of the name of varible
 *
 * It is advertised that a function has only one purpose
 * It is advertised to compiled into a library
 */

/******************************
COMMON INCLUDE FILES
*******************************/
#include <stdio.h>       //printf/sscanf
#define DEBUG 1

/*************************************
judge the given string is submask
[IN]  mask: the string to judge
[RET] 0:the value is invalid
      1:the value is valid

tips 若(n&(n-1))==0则n是2的幂
**************************************/
#include <netinet/in.h>     //in_addr
#include <sys/socket.h>     //inet_aton
int IsValidSubnetMask(const char *mask) 
{
    struct in_addr addr;  
    unsigned int  value[4];   
    unsigned int  count = 0, b = 0;

    if (mask == NULL)
    {
        return (0);
    }

    //if the given string is x.x.x.x type
    if (!inet_aton(mask, &addr))
    {
        return (0);
    }

#ifdef DEBUG
    printf("Debug MaskHex = %X \n", addr.s_addr);
#endif
    sscanf(mask, "%u.%u.%u.%u", &value[3], &value[2], &value[1], &value[0]);

    for(count = 0; count < 4; count++)
    {
        //to get int type value
        b += value[count] << (count * 8);
    }

    b = ~b + 1;  
    if((b & (b - 1)) != 0)//if is 2^n   
    {
        return (0);
    }
    
    return (1);
}

/*************************************
judge the given string is ipaddr
[IN]  ipaddr: the string to judge
[RET] 0:the value is invalid
      1:the value is valid
**************************************/
#include <netinet/in.h>     //in_addr
#include <sys/socket.h>     //inet_aton
int IsValidIpAddress(const char *ipAddr)
{
    struct in_addr ipaddr;
    
    if (ipAddr == NULL)
    {
        return (0);
    }

    if (inet_aton(ipAddr, &ipaddr))
    {
        return (1);
    }
#ifdef DEBUG
    printf("Debug input is not valid ip address\n");
#endif
    return (0);
}

/*************************************
judge the given string is macaddr
[IN]  ipaddr: the string to judge
[RET] 0:the value is invalid
      1:the value is valid
**************************************/
#include <stdlib.h>   //strtoul
#include <string.h>   //strlen
#include <errno.h>    //errno
int IsValidMacAddress(const char *macAddr)
{
    char *endPtr = NULL;
    int ret = 1;
    char *pToken = NULL;
    char *pLast = NULL;
    char buf[32] = {'\0'};
    unsigned int i;
    unsigned long num;

    if (macAddr == NULL || strlen(macAddr) != (18 -1)) //macString len -1
    {
        return (0);
    }

    strcpy(buf, macAddr);

    pToken = strtok_r(buf, ":", &pLast);
    if ((strlen(pToken) != 2) ||
      !strtoul_ret(pToken, NULL, 16, &num)) //if ((errno != 0) || (*localEndPtr != '\0'))
    {
        ret = 0;
    }
    else
    {
        for ( i = 0; i < 5; i++ )
        {
            endPtr = NULL;
            errno = 0;
            pToken = strtok_r(NULL, ":", &pLast);
            if ((strlen(pToken) != 2) ||
              !strtoul_ret(pToken, NULL, 16, &num))
            {
                ret = 0;
                break;
            }
        }
    }

    return (ret);
}

/***************************************************
judge the given string can transformed to base value
[IN]  str: the string to judge
      endptr:not for sure; usually give null
      base: transform base
      val: the trans result
[RET] 0:the value transed wrong
      1:the value transed ok
***************************************************/
int strtoul_ret(char *str, char **endptr, int base, unsigned long *val)
{
    int ret = 1;
    char *endPtr = NULL;
    errno = 0;  /* set to 0 so we can detect ERANGE */

    *val = strtoul(str, &endPtr, base);

    if ((errno != 0) || (*endPtr != '\0'))
    {
        *val = 0;
        ret = 0;
    }

    if (endptr != NULL)
    {
        *endptr = endPtr;
    }
    
    return (ret);
}


static const unsigned int IPADDR_LEN  = 15;//IP地址长度
static const unsigned int MACADDR_LEN = 17;//MAC地址长度
/**
 *判断字符是否为十六进制表示字符，即0~f。
 */
int IsHexChar(char hex)
{
    return ( ( hex >= '0' && hex <= '9' )    ||
                ( hex >= 'a' && hex <= 'f' ) ||
                ( hex >= 'A' && hex <= 'F' ) );
}

int HexCharToInt(char hex)
{
    int val = -1;

    if( hex >= '0' && hex <= '9' )
    {
        val = hex - '0';
    }
    else if( hex >= 'a' && hex <= 'f' ) 
    {
        val = hex - 'a' + 10;
    }
    else if( hex >= 'A' && hex <= 'F' )
    {
        val = hex - 'A' + 10;
    }

    return val;
}

/**
 * 判断输入ip是否有效
 * return 1   有效
 *        0  无效
 */
 #include<arpa/inet.h> //inet_ntoa
int IsIpValid(const char* pAddr)
{
    if ( NULL == pAddr )
    {
        return 0;
    }
    struct in_addr addr;
    if ( inet_aton ( pAddr, &addr ) == 0 )
    {
        return 0;
    }

    char* destIp = ( char* ) inet_ntoa ( addr );
    if ( 0 != strcmp ( pAddr, destIp ) )
    {
        return 0;
    }

    return 1;
}

/**
  判断输入netmask字符串是否有效
 * pNetMask    表示netmask的字符串指针
 * return   1         有效
 *          0         无效
 */
int IsMaskValid(const char* pNetMask)
{
    int i;
    int ret = 0;

    if ( !IsIpValid(pNetMask) )
    {
        return ret;
    }

    unsigned int mask = ntohl( inet_addr(pNetMask) );

    //最高8位必须全为0，且不能为0xffffff
    if ( mask < 0xff || mask == 0xffffffff )
    {
        return ret;
    }

    for (i = 23; i >= 0; --i )
    {
        if ( (mask & (1 << i)) > 0 )
        {
            continue;
        }
        if ( (mask << (8 + 23 - i)) > 0 )
        {
            ret = 0;
            break;
        }
        ret = 1;
        break;
    }

    return ret;
}


/**
 *判断输入mac字符串是否有效,不管中间的分隔符
 * pMac    表示mac地址的字符串指针
 * return  1     有效
 *         0     无效
 */
int IsMacValid(const char* pMac)
{
	unsigned int index;
    if ( NULL == pMac || strlen ( pMac ) != MACADDR_LEN )
    {
        return 0;
    }

    //MAC的第一个字节必须为偶数
    if( HexCharToInt(*(pMac+1)) % 2 != 0 )
    {
        return 0;
    }

    for ( index = 0; index < MACADDR_LEN; ++index )
    {
        if ( 0 == ( ( index + 1 ) % 3 ) ) //不检查间隔为3的字符
        {
            continue;
        }

        //字符必须为十六进制表示字符，即0~f。
        char val = ( * ( pMac + index ) );
        if ( !IsHexChar(val) )
        {
            return 0;
        }
    }

    return 1;
}

/*************************************
get the file size
[IN]  filePath: the file path
[RET] fileSize
**************************************/
#include <sys/types.h>
#include <sys/stat.h>
int GetFileSize(const char *filePath)
{
    int filesize = 0;
    struct stat fileStat;

    if (filePath == NULL)
    {
        return (filesize);  
    }

    memset((void *)&fileStat, 0x0, sizeof(struct stat));

    if (stat(filePath, &fileStat) == 0)
    {  
        filesize = fileStat.st_size;
    }

    return (filesize);  
}
/*************************************
get the specified net seg
[IN]  pIpAddr: ipaddr of net
      pMask: net mask 
[OUT] pNetSeg:the net seg like 192.168.144.0/24
[RET] 0:the value is invalid
      1:the value is valid
**************************************/
int GetNetSegment(const char *pIpAddr, const char *pMask, char *pNetSeg)
{
    unsigned int  ip[4];   
    unsigned int  mask[4];   
    int i, count = 0;    
    unsigned int tmp = 0;

    if (NULL == pNetSeg || !IsValidIpAddress(pIpAddr) || !IsValidSubnetMask(pMask)) //check entry is necessary
    {
        return 0;
    }

    if (sscanf(pIpAddr, "%u.%u.%u.%u", &ip[3], &ip[2], &ip[1], &ip[0]) != 4 ||
        sscanf(pMask, "%u.%u.%u.%u", &mask[3], &mask[2], &mask[1], &mask[0]) != 4)
    {
        return 0;
    }

    for (i = 0; i < 4; i ++)
    {
        ip[i] &= mask[i];  //get the net
        tmp += mask[i] << (i * 8); //get the int type of mask || inet_addr
    }

    for (i = 0; i < 32 && !(tmp & (0x1 << i)); i++); // until get the 1 bit
    sprintf(pNetSeg, "%u.%u.%u.%u/%d", ip[3], ip[2], ip[1], ip[0], (32 - i));

    return 1;
}

/*according to function of find_pid_by_name, in busybox0.6.3/libbb/find_pid_by_name.c*/
/*maybe define a list which member num is big enough, or encounter seg fault*/
#include <dirent.h>
#include <fcntl.h>
/*************************************
find the pid according to name
[IN]  pidName: pidName
[OUT] pidList:the pidllist of pidname
[RET] 0: success
**************************************/
int private_find_pid_by_name(char* pidName, long *pidList)
{
    DIR *dir;
    struct dirent *next;
    FILE *status = NULL;
    char filename[128];
    char buffer[128];
    char name[128];
    
    int i = 0;

    if (pidList == NULL)
    {
        return (2);
    }

    dir = opendir("/proc");
    if (!dir)
    {
        printf("Cannot open /proc");
        return (1);
    }

    while ((next = readdir(dir)) != NULL)
    {
        memset(filename, 0, sizeof(filename));
        memset(buffer, 0, sizeof(buffer));
        memset(name, 0, sizeof(name));

        /* Must skip ".." since that is outside /proc */
        if (strcmp(next->d_name, "..") == 0)
        {
            continue;
        }

        /* If it isn't a number, we don't want it */
        if (!isdigit(*next->d_name))
        {
            continue;
        }

        sprintf(filename, "/proc/%s/status", next->d_name);
        if (! (status = fopen(filename, "r")) )
        {
            continue;
        }
        if (fgets(buffer, 128-1, status) == NULL)
        {
            fclose(status);
            continue;
        }
        fclose(status);

        /* Buffer should contain a string like "Name:   binary_name" */
        sscanf(buffer, "%*s %s", name);
        if (strcmp(name, pidName) == 0)
        {
            pidList[i++] = strtol(next->d_name, NULL, 0);
        }
    }

    return (0);
}

/*interface opration*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /*htonl htons ntohs */
#include <sys/ioctl.h>
#include <net/if.h>
/*************************************
get net device down up status
[IN]: devName
[RET] 0: success

tips:
IFF_RUNNING is supposed to reflect the operational status on a network interface, rather than its administrative one. 
To provide an example, an Ethernet interface may be brought UP by the administrator (e.g. ifconfig eth0 up), 
but it will not be considered operational (i.e. RUNNING as per RFC2863) if the cable is not plugged in
**************************************/
int get_device_status(char* devName)
{
	int skfd = 0;
	struct ifreq ifr;

	skfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(skfd < 0) 
	{
		printf("%s:%d Open socket error!\n", __FILE__, __LINE__);
		return 0;
	}

	strcpy(ifr.ifr_name, devName);

	if(ioctl(skfd, SIOCGIFFLAGS, &ifr) <0 )
	{
		printf("%s:%d IOCTL error!\n", __FILE__, __LINE__);
		printf("Maybe ethernet inferface %s is not valid!", ifr.ifr_name);
		close(skfd);
		return 0;
	}

	if(ifr.ifr_flags & IFF_RUNNING) //IFF_UP
	{
			printf ("UP\n");
			return 1;
	} 
	else 
	{
			printf ("DOWN\n");
			return 0;
	}
}

/*************************************
get and print all net device infomation
[RET] 0: success
**************************************/
int get_all_net_info()
{
	int i=0,j=0;
    int sock;
    struct ifreq *ifr;
    struct ifconf ifc;
    char buf[512];


    if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        perror("socket");
        exit(1);
    }  
    /* 获取所有套接字接口 */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, (char *) &ifc) < 0)
    {
        perror("ioctl-conf:");
        return -1;
    }
    ifr = ifc.ifc_req;

    for(i=(ifc.ifc_len/sizeof(struct ifreq)),j=1; i>0; i--,j++)
    {
        /* 获得第j个网络接口名称 */
        ifr->ifr_ifindex = j;
        if(ioctl(sock, SIOCGIFNAME, (char *)ifr)<0) {perror("NET Name error!");exit(-1);}   
        printf("name (SIOCGIFNAME)= %s\n", ifr->ifr_name);

        /* 获得网卡eth0参数 */
        if (!strcmp(ifr->ifr_name, "eth0"))
        {
            if (ioctl(sock, SIOCGIFFLAGS, (char *)ifr) < 0){perror("Find eth0  error!");exit(-1);}  
            printf("Find eth0  (SIOCGIFFLAGS) = %d\n", ifr->ifr_flags);
        }

        /* 获得MTU */
        if(ioctl(sock, SIOCGIFMTU, (char *)ifr)<0) {perror("MTU error!");exit(-1);} 
        printf("MTU (SIOCGIFMTU)= %d\n", ifr->ifr_mtu);

        /* 获得MAC地址 */
        if(ioctl(sock, SIOCGIFHWADDR, (char *)ifr)<0) {perror("MAC error!");exit(-1);}  
        char  *hw = ifr->ifr_hwaddr.sa_data;
        printf("MAC (SIOCGIFHWADDR)= %02x:%02x:%02x:%02x:%02x:%02x\n", hw[0],hw[1]&0xff,hw[2],hw[3],hw[4],hw[5]);

        /* 查询本地IP */
        if(ioctl(sock, SIOCGIFADDR, (char *)ifr)<0) {perror("Local IP error!");exit(-1);}       
        printf("local addr (SIOCGIFADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr));

        /* 查询广播IP */
        if(ioctl(sock, SIOCGIFBRDADDR, (char *)ifr)<0) {perror("Broadcast error!");exit(-1);}       
        printf("broadcast addr (SIOCGIFBRDADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr));

        /* 查询目的IP */
        if(ioctl(sock, SIOCGIFDSTADDR, (char *)ifr)<0) {perror("Dst IP error!");exit(-1);}  
        printf("dst addr (SIOCGIFDSTADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr));

        /* 查询子网掩码 */
        if(ioctl(sock, SIOCGIFNETMASK, (char *)ifr)<0) {perror("SUB Mask error!");exit(-1);}    
        printf("mask addr (SIOCGIFNETMASK) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr->ifr_addr))->sin_addr));
        ifr++;
        printf("\n");
    }
    return 0;
}

/*************************************
get specified dev info
[IN] devName:net dev name such as eht0
[RET] 0: success
**************************************/
int get_net_info(char *devName)
{
    int sock;
    struct ifreq ifr;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        perror("socket");
        exit(1);
    }  
    
	//querying info according to name or ifr_ifindex is ok
	strcpy(ifr.ifr_name, devName); 
	
	/* 获得MTU */
	if(ioctl(sock, SIOCGIFMTU, &ifr)<0) {perror("MTU error!");exit(-1);} 
	printf("MTU (SIOCGIFMTU)= %d\n", ifr.ifr_mtu);
	
	/* 获得MAC地址 */
	if(ioctl(sock, SIOCGIFHWADDR, &ifr)<0) {perror("MAC error!");exit(-1);}  
	char  *hw = ifr.ifr_hwaddr.sa_data;
	printf("MAC (SIOCGIFHWADDR)= %02x:%02x:%02x:%02x:%02x:%02x\n", hw[0],hw[1]&0xff,hw[2],hw[3],hw[4],hw[5]);
	
	/* 查询本地IP */
	if(ioctl(sock, SIOCGIFADDR, &ifr)<0) {perror("Local IP error!");exit(-1);}       
	printf("local addr (SIOCGIFADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
	
	/* 查询广播IP */
	if(ioctl(sock, SIOCGIFBRDADDR, &ifr)<0) {perror("Broadcast error!");exit(-1);}       
	printf("broadcast addr (SIOCGIFBRDADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
	
	/* 查询目的IP */
	if(ioctl(sock, SIOCGIFDSTADDR, &ifr)<0) {perror("Dst IP error!");exit(-1);}  
	printf("dst addr (SIOCGIFDSTADDR) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
	
	/* 查询子网掩码 */
	if(ioctl(sock, SIOCGIFNETMASK, &ifr)<0) {perror("SUB Mask error!");exit(-1);}    
	printf("mask addr (SIOCGIFNETMASK) = %s\n", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
    return 0;
}

/*************************************
pull specified dev up or down
[IN] interface_name:net dev name such as eht0
     up:the stae to set
        0: down
        1: up 
[RET] 0: success
**************************************/
int interface_updown(char *interface_name, int up)
{
    int s = 0;
    int  flag = 0;
    struct ifreq ifr;

    memset(&ifr, 0x00, sizeof(ifr));
    if(strcmp(interface_name, "lo") == 0)
    {
        printf("can't pull down interface lo");
        return (1);
    }

    if((s = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("socket failure: %s", strerror(errno));
        return (1);
    }

    strcpy(ifr.ifr_name,interface_name);

    if(ioctl(s, SIOCGIFFLAGS, &ifr) < 0)
    {
        printf("SIOCGIFFLAGS failure: %s", strerror(errno));
        close(s);
        return (1);
    }

    if(up)
    {
        flag = IFF_UP|IFF_PROMISC;
        ifr.ifr_ifru.ifru_flags |= flag;
    }
    else
    {
        flag = ~IFF_UP;
        ifr.ifr_ifru.ifru_flags &= flag;
    }

    if(ioctl(s, SIOCSIFFLAGS, &ifr) < 0)
    {
        printf("SIOCSIFFLAGS failure: %s", strerror(errno));
        return (1);
    }

	/*********************************
        set function
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
	sin->sin_family = AF_INET;
	sprintf(ipaddr, "%d.%d.%d.%d", ipaddr[0], ipaddr[1], 
	ipaddr[2], ipaddr[3]);
	inet_pton(AF_INET, ipaddr, &sin->sin_addr);
	ioctl(skfd, SIOCSIFADDR, &ifr);

    if_down()
	ifr.ifr_hwaddr.sa_family = AF_UNIX;
        memcpy(&ifr.ifr_hwaddr.sa_data, &hwaddr, MAC_ADDR_LEN(6));  
    if (ioctl(skfd, SIOCSIFHWADDR, &ifr) < 0)
	if_up()
	**********************************/
    close(s);
    return (0);
}

/*************************************
excute cmd security
[IN] cmd:the cmd to excute
     just like run cmd in shell
[RET] 0: success
**************************************/
int exeCmd(const char *cmd) 
{
	pid_t status;

	status = system(cmd);
	if (-1 == status)
	{
		printf("system error!");
	}
	else
	{
		printf("exit status value = [0x%x]\n", status);
		
		if (WIFEXITED(status))
		{
			if (0 == WEXITSTATUS(status))
			{
				printf("run CMD script successfully.\n");
				return 0;
			}
			else
			{
				printf("run CMD=[%s] script fail, script exit code: %d\n", cmd,WEXITSTATUS(status));
			}
		}
		else
		{
			printf("exit status = [%d]\n", WEXITSTATUS(status));
		}
	}

	return -1;
}

/*************************************
get default gateway using proc file
[OUT] gw:unsigned long type of gateway
[RET] 0: success
**************************************/
int get_defaultgw (unsigned long *gw)
{
    FILE *fp;
    int ret = -1, r;
    char line[256];
    char devname[64], flags[16], *sdest, *sgw;
    unsigned long d, g, m;
    int flgs, ref, use, metric, mtu, win, ir;
    fp = fopen("/proc/net/route" , "r");

    /* Skip the first line. */
    /*if (fscanf(fp, "%*[^\n]\n") < 0) 
    {
		return -1;
    }*/
    if (fgets(line , sizeof(line) , fp) < 0)
    {
        goto EXIT;
    }
    
    while(fgets(line , sizeof(line) , fp))
    {
        r = sscanf(line, "%63s%lx%lx%X%d%d%d%lx%d%d%d\n",
		   devname, &d, &g, &flgs, &ref, &use, &metric, &m,
		   &mtu, &win, &ir);
        printf("devname %s \tdest %lu\t gw %lu\n", devname, d, g);
        printf("gw is %s\n",  inet_ntoa(*(struct in_addr*)&g));
        if(11 == r && d == 0)
        {
            ret = 0;
            *gw = g;
            goto EXIT;
        }
    }

EXIT:
    fclose(fp);
    printf("ret %d\n", ret);
    return ret;
}

//使用sscanf读取数据
/*scanf的format字符串：
空格：也会同样去过滤输入字符串的空格，而且会持续过滤，直到不是空格为止。（空格也包括tab，回车等）
其他字符，（不包括%）：会同样在输入字符里面跳过想用的字符。
%：控制输入一个字段，根据后面的长度，控制符读取数据内容。比如%d等。
%*：会跳过一个输入字段，比如sscanf("123  456","%*d %d",&data); data读取会是456；
%[0-9]:贪婪的读取0-9的字符，作为一个string读取
%[^0-9]:贪婪的读取非0-9的字符，作为一个string读取*/
/*************************************
get default gateway using popen
[OUT] gw:sring type of gateway
[RET] 0: success
**************************************/
int get_defaultgw_2 (char *gw)
{
    FILE *fp;  
    char buf[512];  
    char cmd[128]; 
    char dst[30];    
    char *tmp;  
  
    strcpy(cmd, "route -n");  
    fp = popen(cmd, "r");   
    if(NULL == fp)  
    {  
        perror("popen error");  
        return -1;  
    }
      
    if (fgets(buf , sizeof(buf) , fp) < 0)
    {
        pclose(fp);
        return -1;
    } 

    while(fgets(buf, sizeof(buf), fp) != NULL)  
    {  
        tmp =buf; 
        while(*tmp && isspace(*tmp))  
            ++ tmp;  
        if(strncmp(tmp, "0.0.0.0", strlen("0.0.0.0")) == 0)  
            break;  
    }  
    sscanf(buf, "%*s%s", gw);   //%*s skip first str      
    printf("default gateway:%s\n", gw);  
    pclose(fp); 
    return 0;  
}

/*****************************************
print the function stack info in user space
compile with gcc  -rdynamic -o lib lib.c to show funcname
get line number: addr2line 0x804a45c -e ./lib -f (use -g compile before)

use dump_stack() to print stack in kernel space
/arch/mips/kernel/traps.c dump_stack()
/include/linux/kallsyms.h print_ip_sym
CONFIG_KALLSYMS=y to show funcname
*****************************************/
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h> 
#define MAX_STACK_LAYERS 20
void print_trace (void)
{
    void *array[MAX_STACK_LAYERS];
    size_t size;
    char **strings;
    size_t i;
    size = backtrace (array, MAX_STACK_LAYERS);
    strings = backtrace_symbols (array, size);
    if (NULL == strings)
    {
        perror("backtrace_synbols");
        exit(0);
    }
 
    printf ("Obtained %zd stack frames.\n", size);
    for (i = 0; i < size; i++)
        printf ("%s\n", strings[i]);
 
    free (strings);
    strings = NULL;
}

/* main  for test*/
int main()
{
    unsigned int a =0;
    get_all_net_info();
    exeCmd("ls -a");
    /*unsigned int a =0;
    long pidList[3] = {0};
    if (private_find_pid_by_name("smbd", pidList) == 0)
    {
        printf("SYS_OK\n");
		printf("pid[0] %ld\n", pidList[0]);
		printf("pid[1] %ld\n", pidList[1]);
		printf("pid[2] %ld\n", pidList[2]);
    }*/
}
