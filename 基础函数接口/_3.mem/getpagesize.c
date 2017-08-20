/*************************
size_t getpagesize(void);
函数说明：返回一分页的大小，单位为字节（byte）。
此为系统的分页大小，不一定会和硬件分页大小相同。
返回值:内存分页的大小
#include <unistd.h>
**************************/
#include <stdio.h>
#include <unistd.h>

int main()
{

    printf("pagesize = %d\n", getpagesize());
    return 0;
}

/**************
测试结果
pagesize = 4096
****************/

/***************
同类型函数
***************/