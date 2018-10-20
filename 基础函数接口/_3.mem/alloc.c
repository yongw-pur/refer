/*************************
 void* calloc (size_t num, size_t size);
函数说明：分配连续num个大小为size的空间，并初始化为0
参数：num分配空间个数，size分配空间单位
返回：分配空间的首指针，否则为NULL

void * malloc(size_t size);
函数说明：分配size大小的空间，并不初始化
返回：分配空间的首指针，否则为NULL

void *realloc(void *mem_address, unsigned int newsize)
函数说明:判断当前的指针是否有足够的连续空间，如果有,扩大mem_address指向的地址，并且将mem_address返回
         如果空间不够，先按照newsize指定的大小分配空间，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来mem_address所指内存区域
         原来指针是自动释放，不需要使用free,同时返回新分配的内存区域的首地址。即重新分配存储器块的地址
返回:如果重新分配成功则返回指向被分配内存的指针，否则返回空指针NULL
     当需要扩展的大小（第二个参数）为0并且第一个参数不为NULL时。此时原内存变成“free”的了。
     当没有足够的空间可供扩展的时候。此时，原内存空间的大小维持不变
如果mem_address为NULL，则realloc()和malloc()类似。分配一个newsize的内存块，返回一个指向该内存块的指针。
如果newsize大小为0，那么释放mem_address指向的内存，并返回NULL

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