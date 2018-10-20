/*************************
char * asctime(const struct tm * timeptr);
����˵������tm�ṹָʾ��ʱ��ת��Ϊ�ַ�����ʽ
������timeptrʱ��ṹ��
���أ������ʱ��ת��Ϊ����ʱ��

#include <time.h>


size_t strftime ( char * ptr, size_t maxsize, const char * format, const struct tm * timeptr )
����˵������ʽ�����ʱ��
������ptr����ַ����ռ��ַ��maxsize�ռ��С��format��ʽ������,timeptr tm�ṹʱ��
���أ������ռ�ռ��С
ʶ���ʽ����

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
���Խ��
ctim Sun Sep 17 18:44:17 2017 //current time
asctimel Sun Sep 17 18:44:17 2017
asctime Sun Sep 17 10:44:17 2017
****************/

/***************
ͬ���ͺ���
struct tm *localtime(const time_t * timep);//time_t �ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ����
time_t time(time_t *t);//���شӹ�Ԫ1970��1��1�յ�UTCʱ���0ʱ0��0������������������������
                       //���t ���ǿ�ָ��Ļ����˺���Ҳ�Ὣ����ֵ�浽tָ����ָ���ڴ�
struct tm*gmtime(const time_t*timep);//time_t �ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽���ɽṹtm���� 
char *ctime(const time_t *timep);//time_t�ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽�����ַ�����̬���ء�
                                //�˺����Ѿ���ʱ��ת���ɵ���ʱ��
time_t mktime(strcut tm * timeptr);//����timeptr��ָ��tm�ṹ����ת���ɴӹ�Ԫ1970��1��1��0ʱ0��0�����������UTCʱ��������������
                                  //localtime�������

gmtime ���ؽṹ��tm
int tm_sec ����Ŀǰ������������ΧΪ0-59����������61��
int tm_min ����Ŀǰ��������Χ0-59
int tm_hour ����ҹ�����ʱ������ΧΪ0-23
int tm_mday Ŀǰ�·ݵ���������Χ01-31
int tm_mon ����Ŀǰ�·ݣ���һ�����𣬷�Χ��0-11
int tm_year ��1900 ���������������
int tm_wday һ���ڵ�������������һ���𣬷�ΧΪ0-6
int tm_yday �ӽ���1��1�������������������ΧΪ0-365
int tm_isdst �չ��Լʱ������
�˺������ص�ʱ������δ��ʱ��ת��������UTCʱ�䡣
***************/

/*
tips:ʱ������
sprintf(tzEnv, "GMT%s", reviseTimeZone);
setenv("TZ", tzEnv, 1);
putenv(tzEnv);
tzset();

time(&now);
tm_now = localtime(&now);
strftime(timeStr, sizeof(timeStr),"%Y-%m-%d %H:%M:%S", tm_now);
*/
