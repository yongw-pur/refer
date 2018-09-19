/*************************
ͷ�ļ�: #include <string.h>
int bcmp(const void *s1, const void *s2, int n);
����˵��:�Ƚ��ַ���s1��s2ǰn���ַ��Ƿ����
����:����ַ�����Ȼ���n=0������0�����򷵻ط�0ֵ�(1,-1)�������NULL(���ܴ���NULL);

int memcmp(void *s1, void *s2, unsigned int n);
����˵��:�Ƚ��ڴ���s1��s2��ǰn���ֽ�
����:��s1<s2,����ֵ-1; ��s1==s2������ֵ����0;��s1>s2ʱ,����ֵ1
�Ƚϴ�С������Ϊ:��һ����ƥ����ַ���ֵ�Ĵ�С(unsigned char) �����NULL(���ܴ���NULL)

int strcmp(const char *s1,const char *s2);
����˵��:�Ƚϲ���s1��s2�ַ������ַ�����С�ıȽ����ַ���ֵ��
          strcmp()���Ƚ�s1��һ���ַ�ֵ��ȥs2��һ���ַ�ֵ������ֵΪ0���ټ����Ƚ��¸��ַ�������ֵ��Ϊ0�򽫲�ֵ���ء�
          �����ַ���"Ac"��"ba"�Ƚ���᷵���ַ�"A"(65)��'b'(98)�Ĳ�ֵ(��33)��
����:��s1<s2,����ֵС��0; ��s1==s2������ֵ����0;��s1>s2ʱ,����ֵ����0 (��ͬ��ʵ�ַ��ز�ͬ)

int strcasecmp (const char *s1, const char *s2);
����˵��:�Ƚϲ���s1��s2�ַ������Ƚ�ʱ���Զ����Դ�Сд�Ĳ��졣
          strcasecmp()�Ƚ��ַ���ת��ΪСд��Ȼ��s1��һ���ַ�ֵ��ȥs2��һ���ַ�ֵ
          ����ֵΪ0���ټ����Ƚ��¸��ַ�������ֵ��Ϊ0�򽫲�ֵ���ء�
����:������s1��s2�ַ�����ͬ�򷵻�0����ֵ���ء�

int strncasecmp(const char *s1,const char *s2,size_t n);
����˵��:�Ƚϲ���s1��s2�ַ���ǰn���ַ����Ƚ�ʱ���Զ����Դ�Сд�Ĳ���
����ֵ:��s1<s2,����ֵ-1; ��s1==s2������ֵ����0;��s1>s2ʱ,����ֵ1
**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char *str1 = "abcdefg";
    char *str2 = "abcde";
    char *str3 = "AbCDE";

    printf("%s bcmp3 %s %d\n", str1, str2, bcmp(str1, str2, 3));
    printf("%s bcmp7 %s %d\n", str1, str2, bcmp(str1, str2, 7));
    //printf("NULL bcmp7 %s %d\n",str2, bcmp(NULL, str2, 7)); core dump
    //printf("NULL memcmp7 %s %d\n",str2, memcmp(NULL, str2, 7));core dump
    //printf("NULL strcmp %s %d\n",str2, strcmp(NULL, str2));core dump
    printf("%s memcmp3 %s %d\n", str1, str2, memcmp(str1, str2, 3));
    printf("%s memcmp7 %s %d\n", str1, str2, memcmp(str1, str2, 7));
    printf("%s strcmp %s %d\n", str1, str2, strcmp(str1, str2));
    printf("%s strcasecmp %s %d\n", str1, str2, strcasecmp(str1, str2)); //����'f' - 0 
    printf("%s strncasecmp6 %s %d\n", str1, str2, strncasecmp(str1, str2, 10)); 
}

/**************
���Խ��
abcdefg bcmp3 abcde 0
abcdefg bcmp7 abcde 1
abcdefg memcmp3 abcde 0
abcdefg memcmp7 abcde 1
abcdefg strcmp abcde 1
abcdefg strcasecmp abcde 102
abcdefg strncasecmp6 abcde 1
****************/

/***************
ͬ���ͺ���
***************/

