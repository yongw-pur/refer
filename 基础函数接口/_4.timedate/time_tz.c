/*************************
int gettimeofday(struct timeval * tv , struct timezone * tz )
����˵������ȡʱ����Ϣ��ʱ����tv��ָ�Ľṹ���أ�����ʱ������Ϣ��tz����
������tvʱ����Ϣ��tzʱ����Ϣ
���أ���ǰʱ����Ϣ���ظ�����
timeval�ṹ����Ϊ:
struct timeval{
long tv_sec; //��
long tv_usec; //΢��
};
timezone �ṹ����Ϊ:
struct timezone{
int tz_minuteswest; //��Greenwich ʱ����˶��ٷ���
int tz_dsttime; //�չ��Լʱ���״̬
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
���Խ��
tv_sec; 1505645515
tv_usec; 490735
tz_minuteswest; -480
tz_dsttime: 0
****************/

/***************
ͬ���ͺ���
int settimeofday(const struct timeval *tv,const struct timezone *tz);// ����timeval��ʱ������ʱ��
time_t mktime(strcut tm * timeptr);//��tm�ṹת��Ϊ����
***************/
