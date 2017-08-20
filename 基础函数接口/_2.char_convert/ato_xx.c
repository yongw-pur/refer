/*************************
函数说明：将字符串转换为浮点型数,跳过前面的空格字符，
       直到遇上数字或正负符号才开始做转换,再遇到非数字或字符串结束时('\0')才结束转换
参数：待检测的字符
返回：转换后的结果
#include <stdlib.h>
同 strtod(nptr,(char**)NULL)
对于不能转换为浮点的输入不好判断
**************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	char *a="-100.23";
	char *b="adafa";
	float c;
    
    c = atof(b);
    
	printf("c=%.2f\n",c);
}


/**************
测试结果

****************/

/***************
同类型函数
atoi(char *c) 将字符串转换为整型 同strtol(nptr，(char**)NULL，10)；
atoi(char *c) 将字符串转换为长整型 同strtol(nptr,(char**)NULL,10)；
***************/
