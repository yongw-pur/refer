/*************************
 void* calloc (size_t num, size_t size);
����˵������������num����СΪsize�Ŀռ䣬����ʼ��Ϊ0
������num����ռ������size����ռ䵥λ
���أ�����ռ����ָ�룬����ΪNULL

void * malloc(size_t size);
����˵��������size��С�Ŀռ䣬������ʼ��
���أ�����ռ����ָ�룬����ΪNULL

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