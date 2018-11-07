/*************************
头文件
#include<stdlib.h>
char * getenv(const char *name)
函数说明:取得参数name环境变量的内容。参数name为环境变量的名称，如果该变量存在则会返回指向该内容的指针。环境变量的格式为name＝value
返回:执行成功则返回指向该内容的指针，找不到符合的环境变量名称则返回

int putenv(const char * string)
函数说明:改变或增加环境变量的内容。参数string的格式为name＝value
         如果该环境变量原先存在，则变量内容会依参数string改变，否则此参数内容会成为新的环境变量
返回:执行成功则返回0，有错误发生则返回-1

int setenv(const char *name,const char * value,int overwrite)
函数说明:改变或增加环境变量的内容。参数name为环境变量名称字符串,value则为变量内容，参数overwrite用来决定是否要改变已存在的环境变量
         如果overwrite不为0，而该环境变量原已有内容，则原内容会被改为参数value所指的变量内容。如果overwrite为0，且该环境变量已有内容，则参数value会被忽略
返回:执行成功则返回0，有错误发生时返回-1

int unsetenv(const char *name)
函数说明:删除环境变量name的定义，即使不存在也不算出错

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
测试结果
****************/

/***************
同类型函数:(子进程会继承环境变量)
cat /proc/5595/environ |tr '\0' '\n'
***************/

