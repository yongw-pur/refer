/*************************
char *gcvt(double number��size_t ndigits��char *buf);
����˵������double����ת��Ϊ�ַ�����ndigits��ʾ��ʾ��λ��
ת���ɹ���ת������ַ�������ڲ���bufָ����ָ�Ŀռ䡣
���أ��ַ���ָ�룬�˵�ַ��Ϊbufָ�롣
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
    
    ptr = gcvt(c, 2, buf); //���������ŵ�����λ����ע��buf��Ҫ�ֿռ�
    
	printf("c= %s\n", ptr);
	reurn 1;
}


/**************
���Խ��
c= -3.5
****************/

/***************
ͬ���ͺ���
***************/
