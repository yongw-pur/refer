/*************************
ͷ�ļ�: #include <string.h>
void bzero(void *s,int n);
����˵��:������s��ָ���ڴ�����ǰn���ֽڣ�ȫ����Ϊ��ֵ���൱�ڵ���memset((void*)s,0,size_tn);
n�ĳ��Ȳ��ܳ���s�Ŀռ䣬������������!

void * memset (void *s ,int c, size_t n);
����˵��:������s��ָ���ڴ�����ǰn���ֽ��Բ���c���룬Ȼ�󷵻�ָ��s��ָ��
����:����ָ��s��ָ��
����c������Ϊint�� ��������unsigned char �����Է�Χ��0��255֮��
n�ĳ��Ȳ��ܳ���s�Ŀռ䣬������������!

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char buf[10] = "abcdefghe";
    printf("before buf %s\n", buf);
    memset(buf, 'a', 4);
    printf("memset buf %s  buf[4] %d buf[3] %d\n", buf, buf[4], buf[3]);
    bzero(buf, 4);
    printf("bzero buf %s  buf[4] %d buf[3] %d\n", buf, buf[4], buf[3]);
}

/**************
���Խ��
before buf abcdefghe
memset buf aaaaefghe  buf[4] 101 buf[3] 97
bzero buf   buf[4] 101 buf[3] 0
****************/

/***************
tips:
char *Str;Str="abcdef";Strָ��������ָ������ݲ��ܸ���
char Str[]="abcdef";��ջ�������Ըı�
***************/

