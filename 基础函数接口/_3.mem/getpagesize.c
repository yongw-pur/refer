/*************************
size_t getpagesize(void);
����˵��������һ��ҳ�Ĵ�С����λΪ�ֽڣ�byte����
��Ϊϵͳ�ķ�ҳ��С����һ�����Ӳ����ҳ��С��ͬ��
����ֵ:�ڴ��ҳ�Ĵ�С
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
���Խ��
pagesize = 4096
****************/

/***************
ͬ���ͺ���
***************/