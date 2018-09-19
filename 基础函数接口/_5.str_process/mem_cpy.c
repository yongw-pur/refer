/*************************
头文件: #include <string.h>
void bcopy (const void *src,void *dest ,int n);
函数说明:拷贝src所指的内存内容前n个字节到dest所指的地址;建议使用memcpy()取代

void *memcpy (void * dest ,const void *src, size_t n);
函数说明:拷贝src所指的内存内容前n个字节到dest所指的内存地址上.不会因为遇到字符串结束'\0'而结束
返回:指向dest的指针

void *memmove(void *dest,const void *src,size_t n);
函数说明:拷贝src所指的内存内容前n个字节到dest所指的地址上。
         当src和dest所指的内存区域重叠时，memmove()仍然可以正确的处理(很多时候对这两种调用有优化,都优化到memmove上)
         执行效率上会比使用memcpy()略慢些
         保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中，复制后源区域的内容会被更改
返回:指向dest的指针 

char *strcpy(char *dest,const char *src);
函数说明:将参数src字符串拷贝至参数dest所指的地址
返回:参数dest的字符串起始地址
注意:dest所指的内存空间不够大，可能会造成缓冲溢出(buffer Overflow)的错误情况

char *strncpy(char *dest,const char *src,size_t n);
函数说明:将参数src字符串拷贝前n个字符至参数dest所指的地址 (剩余的字符不拷贝)
返回:参数dest的字符串起始地址

char *strdup(const char *s);
函数说明:先用maolloc()配置与参数s字符串相同的空间大小(使用strlen获得,0之后的数据不会拷贝)，然后将参数s字符串的内容复制到该内存地址，
         然后把该地址返回。该地址最后可以利用free()来释放。
返回:指向复制后的新字符串地址。返回NULL表示内存不足。

char *strcat (char *dest,const char *src);
函数说明:将参数src字符串拷贝到参数dest所指的字符串尾。第一个参数dest要有足够的空间来容纳要拷贝的字符串
返回:参数dest的字符串起始地址

**************************/
#include <stdio.h>
#include <string.h>
void* my_memcpy(void* dst, const void* src, size_t n)
{
    char *tmp = (char*)dst;
    char *s_src = (char*)src;
 
    while(n--) 
    {
        *tmp++ = *s_src++;
    }
    return dst;
}

/*****
*内存覆盖情形:
*1.目的地址在前面，源地址在后面 源a + 2, 目的a
*2.目的地址在后面，源地址在前面 源a, 目的a + 2
******/
void* my_memmove(void* dst, const void* src, size_t n)
{
    char* s_dst;
    char* s_src;
    
    s_dst = (char*)dst;
    s_src = (char*)src;
    if(s_dst>s_src && (s_src+n>s_dst)) //情形2情况解决
    {
        s_dst = s_dst+n-1;
        s_src = s_src+n-1;
        while(n--) 
        {
            *s_dst-- = *s_src--;
        }
    }
    else 
    {
        while(n--) 
        {
            *s_dst++ = *s_src++;
        }
    }
    return dst;
}

main()
{
    char *b;
    char c[]="string(2)";
    char a[30]="string(1)";
    char d[] = "abcdef";
    char e[] = "abcdef";
    
    a[6] = 0;
    printf("original str %s char [7] %d\n", a, a[7]);
    b = strdup(a);
    printf("strdup str %s char [7] %d\n", b, b[7]);
   
    printf("before strncpy() : %s\n",a);
    printf("after strncpy() : %s\n",strncpy(a,c,7));
                                                                                                                                                     
    my_memcpy(d+1, d, 5);
    my_memmove(e+1, e, 5);

    printf("memcpy %s\n", d);
    printf("memmove %s\n", e);
    return 0;
}

/**************
测试结果
original str string char [7] 49
strdup str string char [7] 0
before strncpy() : string
after strncpy() : string(1)
memcpy aaaaaa
memmove aabcde
****************/

/***************
同类型函数
***************/

