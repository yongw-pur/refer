/*************************
char * asctime(const struct tm * timeptr);
函数说明：将tm结构指示的时间转换为字符串形式
参数：timeptr时间结构体
返回：会根据时区转换为当地时间

#include <time.h>


size_t strftime ( char * ptr, size_t maxsize, const char * format, const struct tm * timeptr )
函数说明：格式化输出时间
参数：ptr结果字符串空间地址，maxsize空间大小，format格式化内容,timeptr tm结构时间
返回：输出所占空间大小
识别格式化：

specifier	Replaced by	Example
%a	Abbreviated weekday name *	Thu
%A	Full weekday name *	Thursday
%b	Abbreviated month name *	Aug
%B	Full month name *	August
%c	Date and time representation *	Thu Aug 23 14:55:02 2001
%d	Day of the month (01-31)	23
%H	Hour in 24h format (00-23)	14
%I	Hour in 12h format (01-12)	02
%j	Day of the year (001-366)	235
%m	Month as a decimal number (01-12)	08
%M	Minute (00-59)	55
%p	AM or PM designation	PM
%S	Second (00-61)	02
%U	Week number with the first Sunday as the first day of week one (00-53)	33
%w	Weekday as a decimal number with Sunday as 0 (0-6)	4
%W	Week number with the first Monday as the first day of week one (00-53)	34
%x	Date representation *	08/23/01
%X	Time representation *	14:55:02
%y	Year, last two digits (00-99)	01
%Y	Year	2001
%Z	Timezone name or abbreviation	CDT
%%	A % sign	%
**************************/
#include <stdio.h>
#include <time.h>

main()
{
	time_t timep;
    struct tm *p;
	char buf[80];
	
	time (&timep);
	strftime(buf, 80, "%m;%X", localtime(&timep));
	printf("ctim %s", ctime(&timep));
	printf("asctimel %s",asctime(localtime(&timep)));
	printf("asctime %s",asctime(gmtime(&timep)));
	printf("strtime %s\n", buf);

    
    char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    time_t timep;
    p = localtime(&timep);
    printf("%d%d%d",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);
    printf("%s%d;%d;%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
	
	
}


/**************
测试结果
ctim Sun Sep 17 18:44:17 2017 //current time
asctimel Sun Sep 17 18:44:17 2017
asctime Sun Sep 17 10:44:17 2017
****************/

/***************
同类型函数
struct tm *localtime(const time_t * timep);//time_t 结构中的信息转换成真实世界所使用的时间日期表示方法
time_t time(time_t *t);//返回从公元1970年1月1日的UTC时间从0时0分0秒算起到现在所经过的秒数。
                       //如果t 并非空指针的话，此函数也会将返回值存到t指针所指的内存
struct tm*gmtime(const time_t*timep);//time_t 结构中的信息转换成真实世界所使用的时间日期表示方法，然后将结果由结构tm返回 
char *ctime(const time_t *timep);//time_t结构中的信息转换成真实世界所使用的时间日期表示方法，然后将结果以字符串形态返回。
                                //此函数已经由时区转换成当地时间
time_t mktime(strcut tm * timeptr);//参数timeptr所指的tm结构数据转换成从公元1970年1月1日0时0分0秒算起至今的UTC时间所经过的秒数
                                  //localtime的逆过程

gmtime 返回结构体tm
int tm_sec 代表目前秒数，正常范围为0-59，但允许至61秒
int tm_min 代表目前分数，范围0-59
int tm_hour 从午夜算起的时数，范围为0-23
int tm_mday 目前月份的日数，范围01-31
int tm_mon 代表目前月份，从一月算起，范围从0-11
int tm_year 从1900 年算起至今的年数
int tm_wday 一星期的日数，从星期一算起，范围为0-6
int tm_yday 从今年1月1日算起至今的天数，范围为0-365
int tm_isdst 日光节约时间的旗标
此函数返回的时间日期未经时区转换，而是UTC时间。
***************/

/*
tips:时区处理
sprintf(tzEnv, "GMT%s", reviseTimeZone);
setenv("TZ", tzEnv, 1);
putenv(tzEnv);
tzset();

time(&now);
tm_now = localtime(&now);
strftime(timeStr, sizeof(timeStr),"%Y-%m-%d %H:%M:%S", tm_now);
*/
