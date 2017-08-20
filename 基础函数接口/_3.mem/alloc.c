/*************************
 void* calloc (size_t num, size_t size);
函数说明：分配连续num个大小为size的空间，并初始化为0
参数：num分配空间个数，size分配空间单位
返回：分配空间的首指针，否则为NULL

void * malloc(size_t size);
函数说明：分配size大小的空间，并不初始化
返回：分配空间的首指针，否则为NULL

void free(void *ptr);
函数说明：参数ptr为指向先前由malloc()、calloc()或realloc()所返回的内存指针。
调用free()后ptr所指的内存空间便会被收回。
假若参数ptr所指的内存空间已被收回或是未知的内存地址，可能会有无法预期的情况发生。
若参数ptr为NULL，则free()不会有任何作用。
所以在free一个指针后，应当立马赋值为NULL
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

	for(i = 0; i < 2 * sizeof(int) * 2; i++) //两倍空间，越界没有报错
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
测试结果
****************/

/***************
同类型函数
***************/