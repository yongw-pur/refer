/*************************
ͷ�ļ�
#define _XOPEN_SOURCE
#include<unistd.h>
char *crypt(const char *key, const char *salt)
����˵��:crypt()��ʹ��Data Encryption Standard(DES)���㷨������key��ָ���ַ������Ա��룬
         key�ַ������Ƚ�ȡǰ8���ַ��������˳��ȵ��ַ�û�����塣����saltΪ�����ַ���ɵ��ַ�������a-z��A-Z��0-9��"."��"/"����ɣ�
         ��������ʹ��4096�ֲ�ͬ�ڽ�������һ��������ִ�гɹ���᷵��ָ���������ַ���ָ��
         ����key ��ָ���ַ�������������������������ַ�������Ϊ13���ַ���ǰ�����ַ�Ϊ����salt������ַ���
����:�����ַ��� //ʹ��GCC����ʱ���-lcrypt

#include<stdlib.h>
void *bsearch(const void *key,const void *base,size_t nmemb,size_tsize,int (*compar) (const void*,const void*))
����˵��:���ö�Ԫ����������õ������в������ݡ�
         ����keyָ�������ҵĹؼ����ݣ�����baseָ��Ҫ�����������鿪ͷ��ַ������nmemb���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size����
         ����comparΪһ����ָ�룬������������ж�����Ԫ��֮��Ĵ�С��ϵ��������compar�ĵ�һ��������ָ��Ԫ�����ݴ��ڵڶ���������ָ��Ԫ�����������ش�����0��ֵ������Ԫ�����������ش�0��
����:�ҵ��ؼ������򷵻��ҵ��ĵ�ַ��������������Ҳ����ؼ������򷵻�NULL

void qsort(void * base,size_t nmemb,size_t size,int ( * compar)(const void *, const void *))
����˵��:����baseָ������������鿪ͷ��ַ������nmemb���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size����
         ����comparΪһ����ָ�룬������������ж�����Ԫ�ؼ�Ĵ�С��ϵ��������compar�ĵ�һ��������ָ��Ԫ�����ݴ��ڵڶ���������ָ��Ԫ�����������ش��������ֵ������Ԫ�����������ش�0

void srand (unsigned int seed)
����˵��:����rand()���������ʱ����������ӡ�����seed�����Ǹ�������ͨ����������geypid()��time(0)�ķ���ֵ������seed�����ÿ��seed������ֵͬ��rand()�������������ֵÿ�ξͻ�һ��

int rand(void)
����˵��:����һ�����ֵ����Χ��0��RAND_MAX �䡣
         �ڵ��ô˺������������ǰ������������srand()������������,���δ����������ӣ�rand()�ڵ���ʱ���Զ������������Ϊ1
����: 0��RAND_MAX֮��������ֵ��RAND_MAX������stdlib.h����ֵΪ2147483647
�ú���Ϊ���̰߳�ȫ������������������������ܲ��Ǻܺã��Ѿ����Ƽ�ʹ��

**************************/
#define _XOPEN_SOURCE //������з���ֵΪint���͵�warning����
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int compare(const void *a,const void *b)//
{
    return *(int *)a - *(int *)b; //С����
    //return *(int *)b - *(int *)a; //��С
}

main()
{
    char passwd[13];
    char *key;
    char slat[2];
    key= getpass("Input First Password:");
    slat[0]=key[0]; //slat��������
    slat[1]=key[1];
    strcpy(passwd, crypt(key, slat));
    printf("After crypt(),1st passwd :%s\n", passwd);

    int i = 9;
    int index;
    int *p;
    //int array[]={1,4,5,6,9,11}; // a - b
    //int array[]={20,9,8,3,2,1}; //b - a

    int array[]={5,6,3,17,9,2};
    qsort(array, sizeof(array)/sizeof(int), sizeof(int), compare);
    for (index = 0; index < sizeof(array)/sizeof(int); index++)
        printf("array[%d] %d\n",index, array[index]);
    p = (int *)bsearch(&i, array, sizeof(array)/sizeof(int), sizeof(int), compare);
    printf("bsearch data %d\n", *p);

    
    int j;
    srand((int)time(0));
    for(j = 0; j < 10; j++)
    {
        printf(" %d ", 1+(int)(10.0*rand()/(RAND_MAX+1.0)));
    }
}



/**************
���Խ��
****************/

/***************
ͬ���ͺ���:
void *lfind (const void *key,const void *base,size_t *nmemb,size_t size,int(* compar) (const void * ,const void *))
���Բ��ң�compare���ж�����Ԫ���Ƿ���ͬ��������compar����ظ�������ָ��Ԫ�����ݺ͵ڶ���������ָ��Ԫ��������ͬʱ�򷵻�0������Ԫ�����ݲ���ͬ�򷵻ط�0ֵ�����Ҳ����ؼ�����ʱlfind()����NULL

void *lsearch(const void * key ,const void * base ,size_t * nmemb,size_t size, int ( * compar) (const void * ,const void *))
lsearch()���Ҳ����ؼ�����ʱ�������Ѹñ����ݼ�������β��

void srandom(unsigned int seed)��������ֵ��һ���롰��ǰʱ�� + ����ID����Ϊ���ӣ����û�õ��øú�������ͨ��random���ص�Ĭ������ֵΪ1
long int random(void) 0-RAND_MAX ֮���һ�� long �����������ú��������һ���ǳ�������ֵ���Ƽ�ʹ��)
***************/

