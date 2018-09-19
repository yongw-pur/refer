/*************************
ͷ�ļ�: #include <string.h>
void bcopy (const void *src,void *dest ,int n);
����˵��:����src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ�ĵ�ַ;����ʹ��memcpy()ȡ��

void *memcpy (void * dest ,const void *src, size_t n);
����˵��:����src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ���ڴ��ַ��.������Ϊ�����ַ�������'\0'������
����:ָ��dest��ָ��

void *memmove(void *dest,const void *src,size_t n);
����˵��:����src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ�ĵ�ַ�ϡ�
         ��src��dest��ָ���ڴ������ص�ʱ��memmove()��Ȼ������ȷ�Ĵ���(�ܶ�ʱ��������ֵ������Ż�,���Ż���memmove��)
         ִ��Ч���ϻ��ʹ��memcpy()����Щ
         ��֤Դ���ڱ�����֮ǰ���ص�������ֽڿ�����Ŀ�������У����ƺ�Դ��������ݻᱻ����
����:ָ��dest��ָ�� 

char *strcpy(char *dest,const char *src);
����˵��:������src�ַ�������������dest��ָ�ĵ�ַ
����:����dest���ַ�����ʼ��ַ
ע��:dest��ָ���ڴ�ռ䲻���󣬿��ܻ���ɻ������(buffer Overflow)�Ĵ������

char *strncpy(char *dest,const char *src,size_t n);
����˵��:������src�ַ�������ǰn���ַ�������dest��ָ�ĵ�ַ (ʣ����ַ�������)
����:����dest���ַ�����ʼ��ַ

char *strdup(const char *s);
����˵��:����maolloc()���������s�ַ�����ͬ�Ŀռ��С(ʹ��strlen���,0֮������ݲ��´��)��Ȼ�󽫲���s�ַ��������ݸ��Ƶ����ڴ��ַ��
         Ȼ��Ѹõ�ַ���ء��õ�ַ����������free()���ͷš�
����:ָ���ƺ�����ַ�����ַ������NULL��ʾ�ڴ治�㡣

char *strcat (char *dest,const char *src);
����˵��:������src�ַ�������������dest��ָ���ַ���β����һ������destҪ���㹻�Ŀռ�������Ҫ�������ַ���
����:����dest���ַ�����ʼ��ַ

**************************/
#include <stdio.h>
#include <string.h>
void* my_memcpy(void* dst, const void* src, size_t n)
{
    char *tmp = (char*)dst;
    char *s_src = (char*)src;
 
    while(n--) 
    {
        *tmp++ = *s_src++;
    }
    return dst;
}

/*****
*�ڴ渲������:
*1.Ŀ�ĵ�ַ��ǰ�棬Դ��ַ�ں��� Դa + 2, Ŀ��a
*2.Ŀ�ĵ�ַ�ں��棬Դ��ַ��ǰ�� Դa, Ŀ��a + 2
******/
void* my_memmove(void* dst, const void* src, size_t n)
{
    char* s_dst;
    char* s_src;
    
    s_dst = (char*)dst;
    s_src = (char*)src;
    if(s_dst>s_src && (s_src+n>s_dst)) //����2������
    {
        s_dst = s_dst+n-1;
        s_src = s_src+n-1;
        while(n--) 
        {
            *s_dst-- = *s_src--;
        }
    }
    else 
    {
        while(n--) 
        {
            *s_dst++ = *s_src++;
        }
    }
    return dst;
}

main()
{
    char *b;
    char c[]="string(2)";
    char a[30]="string(1)";
    char d[] = "abcdef";
    char e[] = "abcdef";
    
    a[6] = 0;
    printf("original str %s char [7] %d\n", a, a[7]);
    b = strdup(a);
    printf("strdup str %s char [7] %d\n", b, b[7]);
   
    printf("before strncpy() : %s\n",a);
    printf("after strncpy() : %s\n",strncpy(a,c,7));
                                                                                                                                                     
    my_memcpy(d+1, d, 5);
    my_memmove(e+1, e, 5);

    printf("memcpy %s\n", d);
    printf("memmove %s\n", e);
    return 0;
}

/**************
���Խ��
original str string char [7] 49
strdup str string char [7] 0
before strncpy() : string
after strncpy() : string(1)
memcpy aaaaaa
memmove aabcde
****************/

/***************
ͬ���ͺ���
***************/

