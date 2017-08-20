/*************************
long int strtol(const char *nptr,char **endptr,int base);
函数说明：将字符串转换成长整型数,跳过前面的空格字符，直到遇上数字或正负符
转换成功，转换后的字符串会放在参数buf指针所指的空间。
参数: base代表采用的进制方式，如base值为10则采用10进制，若base值为16则采用16进制等。当base值为0时则是采用10进制做转换
返回：返回转换后的长整型数，否则返回ERANGE并将错误代码存入errno中。

可以根据endptr判断参数是否能够正常转换
#include <stdlib.h>
**************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	char a[]="1000000000";
	char b[]="1000000000";
	char c[]="ffff";
	printf("a=%d\n",strtol(a,(char **)NULL,10));
	printf("b=%d\n",strtol(b,(char **)NULL,2));
	printf("c=%d\n",strtol(c,(char **)NULL,16));

    return(0);
}


/**************
测试结果
a=1000000000
b=512
c=65535
****************/

/***************
同类型函数
unsigned long int strtoul(const char *nptr,char **endptr,int base);
***************/
