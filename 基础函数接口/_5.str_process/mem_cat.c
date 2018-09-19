/*************************
头文件: #include <string.h>
char *strcat (char *dest,const char *src);
函数说明:将参数src字符串拷贝到参数dest所指的字符串尾。
         第一个参数dest要有足够的空间来容纳要拷贝的字符串。
返回:参数dest的字符串起始地址

char * strncat(char *dest,const char *src,size_t n);
函数说明:将参数src字符串拷贝n个字符到参数dest所指的字符串尾。
         如果n大于字符串src的长度，仅将src指向的字符串内容追加到dest的尾部
         将dest字符串最后的'\0'覆盖掉，字符追加完成后，再追加'\0'
         第一个参数dest要有足够的空间来容纳要拷贝的字符串。(src中遇到0或者n停止)
返回:参数dest的字符串起始地址

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char a[40]="string(1)";
    char b[]="string(2)";
    b[6] = 0;
    printf("before strnact() :%s\n", a);
    printf("after strncat() :%s\n", strncat(a, b, 20));
}

/**************
测试结果
before strnact() :string(1)
after strncat() :string(1)string
****************/

/***************
strlen()用来计算指定的字符串s的长度，不包括结束字符"\0"
***************/

