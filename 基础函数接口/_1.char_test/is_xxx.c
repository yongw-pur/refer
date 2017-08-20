/*************************
函数说明：检查参数是否是数字或字母等同于 isdigit()||isalpha()
参数：待检测的参数//实际上都会转换为数字
返回：1:参数为数字或字母
      0：参数为其他
**************************/
#include <ctype.h>
#include <stdio.h>

int main()
{
	int index;
	char str[] = "123c@#FDsP[e?";
	for (index = 0; str[index] != 0; index++)
	{
		if (isalnum(str[index]))
		{
			printf("%c is alphanumeric char\n", str[index]);	
		}	
	}
	
	return 1;
}

/**************
测试结果
1 is alphanumeric char
2 is alphanumeric char
3 is alphanumeric char
c is alphanumeric char
F is alphanumeric char
D is alphanumeric char
s is alphanumeric char
P is alphanumeric char
e is alphanumeric char
****************/

/***************
同类型函数
isalpha(c) 判断参数是否为英文字母
isdigit(c) 判断参数是否为阿拉伯数字
isascii(c) 判断参数是否为accii码字符(即C 0~127)
iscntrl(c) 判断参数是否为ASCII控制码(即C 0~30)
isprint(c)/isgraph(c) 判断参数是否可打印字符（非空 空格tab，可打印）
islower(c) 判断参数是否为小写英文字母
isupper(c) 判断参数是否为大写英文字母
isxdigit(c)判断参数是否为16进制数字（0-F）
isspace(c) 判断参数是否为空格字符。（空格，\t, \r \n, \v垂直定位, \f翻页）
ispunct(c) 判断参数是否为标点符号或特殊符号（非空，非字符，非数字）
***************/
