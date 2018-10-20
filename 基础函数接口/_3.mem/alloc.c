/*************************
 void* calloc (size_t num, size_t size);
����˵������������num����СΪsize�Ŀռ䣬����ʼ��Ϊ0
������num����ռ������size����ռ䵥λ
���أ�����ռ����ָ�룬����ΪNULL

void * malloc(size_t size);
����˵��������size��С�Ŀռ䣬������ʼ��
���أ�����ռ����ָ�룬����ΪNULL

void *realloc(void *mem_address, unsigned int newsize)
����˵��:�жϵ�ǰ��ָ���Ƿ����㹻�������ռ䣬�����,����mem_addressָ��ĵ�ַ�����ҽ�mem_address����
         ����ռ䲻�����Ȱ���newsizeָ���Ĵ�С����ռ䣬��ԭ�����ݴ�ͷ��β�������·�����ڴ����򣬶����ͷ�ԭ��mem_address��ָ�ڴ�����
         ԭ��ָ�����Զ��ͷţ�����Ҫʹ��free,ͬʱ�����·�����ڴ�������׵�ַ�������·���洢����ĵ�ַ
����:������·���ɹ��򷵻�ָ�򱻷����ڴ��ָ�룬���򷵻ؿ�ָ��NULL
     ����Ҫ��չ�Ĵ�С���ڶ���������Ϊ0���ҵ�һ��������ΪNULLʱ����ʱԭ�ڴ��ɡ�free�����ˡ�
     ��û���㹻�Ŀռ�ɹ���չ��ʱ�򡣴�ʱ��ԭ�ڴ�ռ�Ĵ�Сά�ֲ���
���mem_addressΪNULL����realloc()��malloc()���ơ�����һ��newsize���ڴ�飬����һ��ָ����ڴ���ָ�롣
���newsize��СΪ0����ô�ͷ�mem_addressָ����ڴ棬������NULL

void free(void *ptr);
����˵��������ptrΪָ����ǰ��malloc()��calloc()��realloc()�����ص��ڴ�ָ�롣
����free()��ptr��ָ���ڴ�ռ��ᱻ�ջء�
��������ptr��ָ���ڴ�ռ��ѱ��ջػ���δ֪���ڴ��ַ�����ܻ����޷�Ԥ�ڵ����������
������ptrΪNULL����free()�������κ����á�
������freeһ��ָ���Ӧ������ֵΪNULL
#include <stdlib.h>
**************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p, *q;
	int i = 0;

	p = calloc(2, sizeof(int));
    
	q = p;
	if( p == NULL)
	{
		printf("memory is not enough\n");
		return -1;
	}

	for(i = 0; i < 2 * sizeof(int) * 2; i++) //�����ռ䣬Խ��û�б���
	{
		*p = 'c';
		printf("curr index %d position%p char %c\n", i, p, *p);
		p++;
	}

	free(q);
	q = NULL;
	return 1;
}


/**************
���Խ��
****************/

/***************
ͬ���ͺ���
***************/