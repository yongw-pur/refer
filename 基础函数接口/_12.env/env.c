/*************************
ͷ�ļ�
#include<stdlib.h>
char * getenv(const char *name)
����˵��:ȡ�ò���name�������������ݡ�����nameΪ�������������ƣ�����ñ���������᷵��ָ������ݵ�ָ�롣���������ĸ�ʽΪname��value
����:ִ�гɹ��򷵻�ָ������ݵ�ָ�룬�Ҳ������ϵĻ������������򷵻�

int putenv(const char * string)
����˵��:�ı�����ӻ������������ݡ�����string�ĸ�ʽΪname��value
         ����û�������ԭ�ȴ��ڣ���������ݻ�������string�ı䣬����˲������ݻ��Ϊ�µĻ�������
����:ִ�гɹ��򷵻�0���д������򷵻�-1

int setenv(const char *name,const char * value,int overwrite)
����˵��:�ı�����ӻ������������ݡ�����nameΪ�������������ַ���,value��Ϊ�������ݣ�����overwrite���������Ƿ�Ҫ�ı��Ѵ��ڵĻ�������
         ���overwrite��Ϊ0�����û�������ԭ�������ݣ���ԭ���ݻᱻ��Ϊ����value��ָ�ı������ݡ����overwriteΪ0���Ҹû��������������ݣ������value�ᱻ����
����:ִ�гɹ��򷵻�0���д�����ʱ����-1

int unsetenv(const char *name)
����˵��:ɾ����������name�Ķ��壬��ʹ������Ҳ�������

**************************/
#include<stdio.h>
#include <stdlib.h>
extern char** environ;
int printenv(void)
{
	int i;
	for(i=0; environ[i];i++)
	{
		printf("%s\n", environ[i]);
	}
	return 0;
}

main()
{
    printenv();
    printf("\n\n\n\n----\n");
    char *p;
    if((p = getenv("USER")))
    printf("USER =%s\n", p);
    putenv("USER=test");
    printf("USER %s\n", getenv("USER"));
    printenv();
}


/**************
���Խ��
****************/

/***************
ͬ���ͺ���:(�ӽ��̻�̳л�������)
cat /proc/5595/environ |tr '\0' '\n'
***************/

