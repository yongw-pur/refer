/*************************
int toascii(int c)
����˵������������ת���ɺϷ���ASCII ���ַ�
		������cת����7λ��unsigned charֵ���ڰ�λ��ᱻ��������ַ����ᱻת��ASCII���ַ�
����: ���൱�ڼ�ȥ128����
���أ���ת���ɹ���ASCII���ַ�ֵ���ء�
���Ը���endptr�жϲ����Ƿ��ܹ�����ת��
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
���Խ��
before toascii() : a value =217()
after toascii() : a value =89(Y)
****************/

/***************
ͬ���ͺ���
tolower(int c) ��c��д��ĸ��ת���󷵻أ�����ֱ�ӷ���ԭʼֵ
toupper(int c) ��cСд��ĸ��ת���󷵻أ�����ֱ�ӷ���ԭʼֵ
***************/
