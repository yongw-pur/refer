/*************************
����˵�����������Ƿ������ֻ���ĸ��ͬ�� isdigit()||isalpha()
�����������Ĳ���//ʵ���϶���ת��Ϊ����
���أ�1:����Ϊ���ֻ���ĸ
      0������Ϊ����
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
���Խ��
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
ͬ���ͺ���
isalpha(c) �жϲ����Ƿ�ΪӢ����ĸ
isdigit(c) �жϲ����Ƿ�Ϊ����������
isascii(c) �жϲ����Ƿ�Ϊaccii���ַ�(��C 0~127)
iscntrl(c) �жϲ����Ƿ�ΪASCII������(��C 0~30)
isprint(c)/isgraph(c) �жϲ����Ƿ�ɴ�ӡ�ַ����ǿ� �ո�tab���ɴ�ӡ��
islower(c) �жϲ����Ƿ�ΪСдӢ����ĸ
isupper(c) �жϲ����Ƿ�Ϊ��дӢ����ĸ
isxdigit(c)�жϲ����Ƿ�Ϊ16�������֣�0-F��
isspace(c) �жϲ����Ƿ�Ϊ�ո��ַ������ո�\t, \r \n, \v��ֱ��λ, \f��ҳ��
ispunct(c) �жϲ����Ƿ�Ϊ�����Ż�������ţ��ǿգ����ַ��������֣�
***************/
