/*************************
int gettimeofday(struct timeval * tv , struct timezone * tz )
函数说明：获取时间信息：时间由tv所指的结构返回，当地时区的信息由tz返回
参数：tv时间信息，tz时区信息
返回：当前时间信息返回给参数
timeval结构定义为:
struct timeval{
long tv_sec; //秒
long tv_usec; //微秒
};
timezone 结构定义为:
struct timezone{
int tz_minuteswest; //和Greenwich 时间差了多少分钟
int tz_dsttime; //日光节约时间的状态
};

#include <sys/time.h>
#include <unistd.h>
**************************/
#include <stdio.h>
#include<sys/time.h>
#include<unistd.h>
main()
{
	struct timeval tv;
	struct timezone tz;
	
	gettimeofday(&tv , &tz);
	printf("tv_sec; %ld\n", tv.tv_sec);
	printf("tv_usec; %ld\n",tv.tv_usec);
	printf("tz_minuteswest; %d\n", tz.tz_minuteswest);
	printf("tz_dsttime: %d\n",tz.tz_dsttime);
}

/**************
测试结果
tv_sec; 1505645515
tv_usec; 490735
tz_minuteswest; -480
tz_dsttime: 0
****************/

/***************
同类型函数
int settimeofday(const struct timeval *tv,const struct timezone *tz);// 根据timeval和时区设置时间
time_t mktime(strcut tm * timeptr);//将tm结构转换为秒数
***************/
