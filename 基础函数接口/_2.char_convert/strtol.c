/*************************
long int strtol(const char *nptr,char **endptr,int base);
����˵�������ַ���ת���ɳ�������,����ǰ��Ŀո��ַ���ֱ���������ֻ�������
ת���ɹ���ת������ַ�������ڲ���bufָ����ָ�Ŀռ䡣
����: base������õĽ��Ʒ�ʽ����baseֵΪ10�����10���ƣ���baseֵΪ16�����16���Ƶȡ���baseֵΪ0ʱ���ǲ���10������ת��
���أ�����ת����ĳ������������򷵻�ERANGE��������������errno�С�

���Ը���endptr�жϲ����Ƿ��ܹ�����ת��
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
���Խ��
a=1000000000
b=512
c=65535
****************/

/***************
ͬ���ͺ���
unsigned long int strtoul(const char *nptr,char **endptr,int base);
***************/
