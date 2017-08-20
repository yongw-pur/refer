/*************************
char *gcvt(double number，size_t ndigits，char *buf);
函数说明：将double参数转换为字符串，ndigits表示显示的位数
转换成功，转换后的字符串会放在参数buf指针所指的空间。
返回：字符串指针，此地址即为buf指针。
#include <stdlib.h>
**************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	double c = -3.456;
	char buf[24] = {0};
    char *ptr;
    
    ptr = gcvt(c, 2, buf); //不包括符号的数字位数，注意buf需要分空间
    
	printf("c= %s\n", ptr);
	reurn 1;
}


/**************
测试结果
c= -3.5
****************/

/***************
同类型函数
***************/
