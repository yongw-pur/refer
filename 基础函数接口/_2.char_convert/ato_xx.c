/*************************
����˵�������ַ���ת��Ϊ��������,����ǰ��Ŀո��ַ���
       ֱ���������ֻ��������Ųſ�ʼ��ת��,�����������ֻ��ַ�������ʱ('\0')�Ž���ת��
�������������ַ�
���أ�ת����Ľ��
#include <stdlib.h>
ͬ strtod(nptr,(char**)NULL)
���ڲ���ת��Ϊ��������벻���ж�
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
���Խ��

****************/

/***************
ͬ���ͺ���
atoi(char *c) ���ַ���ת��Ϊ���� ͬstrtol(nptr��(char**)NULL��10)��
atoi(char *c) ���ַ���ת��Ϊ������ ͬstrtol(nptr,(char**)NULL,10)��
***************/
