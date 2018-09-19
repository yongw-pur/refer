/*************************
ͷ�ļ�: #include <string.h>
���ҵ��İ�������
char *index( const char *s, int c);
����˵��:�ҳ�����s�ַ����е�һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
         �ַ��������ַ�(NULL)Ҳ��Ϊ�ַ���һ����,Ҳ������.(��0Ϊ�����Ľ���)
����:����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0

void *memchr(const void *s,int c,size_t n);
����˵��:��ͷ��ʼ��Ѱs��ָ���ڴ�����ǰn���ֽڣ�ֱ�����ֵ�һ��ֵΪc���ֽڣ��򷵻�ָ����ֽڵ�ָ�롣
         (��nΪ�����Ľ������ַ�����������0��Ҳ��������ע�ⲻ�ܳ���s�ķ�Χ)
����:����ҵ�ָ�����ֽ��򷵻ظ��ֽڵ�ָ�룬���򷵻�0

char * rindex( const char *s,int c);
����˵��:�ҳ�����s�ַ��������һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
         strlen�����ַ����ĳ���, �ַ��������ַ�(NULL)Ҳ��Ϊ�ַ���һ����
����:����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵĵ�ַ�����򷵻�0

char * strchr (const char *s,int c);
����˵��:�ҳ�����s�ַ����е�һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
����:����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��

char * strrchr(const char *s, int c);
����˵��:�ҳ�����s�ַ��������һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ����
����:����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0

char *strpbrk(const char *s,const char *accept);
����˵��:�ҳ�����s �ַ��������ȳ��ִ��ڲ���accept�ַ����е������ַ���
����: ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��(s���Ƿ����accpet�е��ַ�)

size_t strspn (const char *s,const char *accept);
����˵��:�Ӳ���s �ַ����Ŀ�ͷ�����������ַ�������Щ�ַ�����ȫ��accept ��ָ�ַ����е��ַ���
         ��strspn()���ص���ֵΪn��������ַ���s ��ͷ������n���ַ����������ַ���accept�ڵ��ַ�
         ��һ������accpet�е�λ��
����:�ַ���s��ͷ���������ַ���accept�ڵ��ַ���Ŀ(0û��) s[index]Ϊ������accpet�ĵ�һ��Ԫ�ء�����0���бȽ�

char *strstr(const char *s,const char *key);
����˵��:���ַ���s����Ѱ�ַ���key��������һ�γ��ֵĵ�ַ����
����:ָ���ַ�����һ�γ��ֵĵ�ַ�����򷵻�0.key�е�һ���ַ���λ��

char *strtok(char *s,const char *delim);
����˵��:���ַ����ָ��һ����Ƭ�Ρ�����sָ�����ָ���ַ���������delim��Ϊ�ָ��ַ���
         ��strtok()�ڲ���s���ַ����з��ֵ�����delim�ķָ��ַ�ʱ��Ὣ���ַ���Ϊ\0 �ַ���
         �ڵ�һ�ε���ʱ��strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��
         ÿ�ε��óɹ��򷵻���һ���ָ����ַ���ָ��(��ָ̬�뱣����һ�����ݵ�λ��)
����:��һ���ָ����ַ���ָ�룬������޴ӷָ��򷵻�NULL

char *strsep(char **stringp, const char *delim);
����˵��:�ַ���Ϊһ���ַ�������stringpָ���λ�������ɨ�裬����delimָ����ַ����е��ַ��󣬽����ַ��滻ΪNULL������stringpָ��ĵ�ַ��
         �����ڷָ�ؼ��֡��������ַ���֮��ֻ���ϸ����һ�Ρ������
         ������ؼ��֡����ַ���֮����������, *key_point == 0��ʱ��continue
����:��һ���ָ����ַ���ָ�룬������޴ӷָ��򷵻�NULL

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char *p;
    int count;
    char s[] ="0123456789012345678901234567890";
    //s[6] = 0;
    
    p = index(s,'9');
    p = rindex(s,'9');
    p = strchr(s, '9');
    p = memchr(s,'9', 100);
    p= strpbrk(s,"4398");/*3 ��������s �ַ������ҵ�*/
    count = strspn(s, "0123456789012345678901234567890");
    p = strstr(s, "23");
    printf("%s %d\n", p, count);

    
    char s1[]="ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    char *delim="-: ";
    char *q;
	for(q = strtok(s1, delim); q != NULL; q = strtok(NULL, delim)) {
		printf("token %s\n", q);
	}
    printf("\n");
    /*printf("%s ", strtok(s1,delim));
    while((q=strtok(NULL,delim)))
        printf("%s ",q);*/

    char source[] = "hello, world! welcome to china!";
	char delim2[] = " ,!";
 
	char *s2 = source; //����ֱ��ʹ�������ַ�������ַ�����޸�
	char *token;
	for(token = strsep(&s2, delim2); token != NULL; token = strsep(&s2, delim2)) 
    {
        if (*token == 0) //������delim��һ������
            continue;
        printf("token %s\n", token);
	}
}

/**************
���Խ��
23456789012345678901234567890 31
token ab
token cd
token ef;gh
token i
token jkl;mnop;qrs
token tu
token vwx
token y;z

token hello
token world
token welcome
token to
token china
****************/

/***************
˵��:
strtok, strsep:
�������Ĵ����������Ķ���ַ�����delim,strtok�᷵��NULL����strsep�᷵�ؿմ�""��
����������strsep�����ָ��ַ���������з���ֵ�Ƿ��ǿմ����жϡ�
��������þ�������ʹ��strtok��ת��ʹ���ٶȸ���strsep��
***************/

