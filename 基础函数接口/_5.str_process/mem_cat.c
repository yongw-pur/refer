/*************************
ͷ�ļ�: #include <string.h>
char *strcat (char *dest,const char *src);
����˵��:������src�ַ�������������dest��ָ���ַ���β��
         ��һ������destҪ���㹻�Ŀռ�������Ҫ�������ַ�����
����:����dest���ַ�����ʼ��ַ

char * strncat(char *dest,const char *src,size_t n);
����˵��:������src�ַ�������n���ַ�������dest��ָ���ַ���β��
         ���n�����ַ���src�ĳ��ȣ�����srcָ����ַ�������׷�ӵ�dest��β��
         ��dest�ַ�������'\0'���ǵ����ַ�׷����ɺ���׷��'\0'
         ��һ������destҪ���㹻�Ŀռ�������Ҫ�������ַ�����(src������0����nֹͣ)
����:����dest���ַ�����ʼ��ַ

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char a[40]="string(1)";
    char b[]="string(2)";
    b[6] = 0;
    printf("before strnact() :%s\n", a);
    printf("after strncat() :%s\n", strncat(a, b, 20));
}

/**************
���Խ��
before strnact() :string(1)
after strncat() :string(1)string
****************/

/***************
strlen()��������ָ�����ַ���s�ĳ��ȣ������������ַ�"\0"
***************/

