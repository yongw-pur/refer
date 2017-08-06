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

tips »Ù(n&(n-1))==0‘Ún «2µƒ√›
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


/* main  for test*/
int main()
{
    unsigned int a =0;
    if (IsValidMacAddress("00:02:03:ef:44:66"))
    {
        printf("SYS_OK");
    }
}

