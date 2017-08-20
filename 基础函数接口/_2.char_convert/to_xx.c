/*************************
int toascii(int c)
函数说明：将整型数转换成合法的ASCII 码字符
		将参数c转换成7位的unsigned char值，第八位则会被清除，此字符即会被转成ASCII码字符
参数: （相当于减去128？）
返回：将转换成功的ASCII码字符值返回。
可以根据endptr判断参数是否能够正常转换
#include<ctype.h>
**************************/
#include <ctype.h>
#include <stdio.h>


int main()
{
	int a=217;
	char b;
	printf("before toascii () : a value =%d(%c)\n", a, a);
	b = toascii(a);
	printf("after toascii() : a value =%d(%c)\n", b, b);

    return(0);
}


/**************
测试结果
before toascii() : a value =217()
after toascii() : a value =89(Y)
****************/

/***************
同类型函数
tolower(int c) 若c大写字母则转换后返回，否则直接返回原始值
toupper(int c) 若c小写字母则转换后返回，否则直接返回原始值
***************/
