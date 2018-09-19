/*************************
头文件: #include <string.h>
void bzero(void *s,int n);
函数说明:将参数s所指的内存区域前n个字节，全部设为零值。相当于调用memset((void*)s,0,size_tn);
n的长度不能超过s的空间，否则会产生意外!

void * memset (void *s ,int c, size_t n);
函数说明:将参数s所指的内存区域前n个字节以参数c填入，然后返回指向s的指针
返回:返回指向s的指针
参数c虽声明为int， 但必须是unsigned char ，所以范围在0到255之间
n的长度不能超过s的空间，否则会产生意外!

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char buf[10] = "abcdefghe";
    printf("before buf %s\n", buf);
    memset(buf, 'a', 4);
    printf("memset buf %s  buf[4] %d buf[3] %d\n", buf, buf[4], buf[3]);
    bzero(buf, 4);
    printf("bzero buf %s  buf[4] %d buf[3] %d\n", buf, buf[4], buf[3]);
}

/**************
测试结果
before buf abcdefghe
memset buf aaaaefghe  buf[4] 101 buf[3] 97
bzero buf   buf[4] 101 buf[3] 0
****************/

/***************
tips:
char *Str;Str="abcdef";Str指向常量区，指向的内容不能改了
char Str[]="abcdef";在栈区，可以改变
***************/

