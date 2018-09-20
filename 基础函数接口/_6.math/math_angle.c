/*************************
#include<math.h>
double acos (double x);
����˵��:�������x�ķ�����ֵ,����x��ΧΪ-1��1
����:����0��PI֮��ļ���������λΪ���ȣ��ں������нǶȾ��Ի�������ʾ EDOM����x������Χ

double atan2(double y,double x);
����˵��:�������y/x�ķ�����ֵ
����:-PI/2 ��PI/2 ֮��ļ�����(����lm)

double cosh(double x);
����˵��:�������x��˫��������ֵ;��ѧ����ʽΪ:(exp(x)+exp(-x))/2��
����:����x��˫��������ֵ

double sinh( double x);
����˵��:�������x��˫��������ֵ,��ѧ����ʽΪ:(exp(x)-exp(-x))/2��
����:����x��˫��������ֵ

double tanh(double x);
����˵��:�������x��˫��������ֵ,��ѧ����ʽΪ:sinh(x)/cosh(x)
����:����x��˫��������ֵ

**************************/
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>//strerror
#include <errno.h> //errno
//#include <complex.h>

int main()
{ 
   printf("cosh(0.5) %lf\n", cosh(0.5));
   printf("(exp(0.5)+exp(-0.5))/2 %lf\n", (exp(0.5)+exp(-0.5))/2);
   printf("acos(-0.5) %lf\n", acos(-0.5));

}

/**************
���Խ��
cosh(0.5) 1.127626
(exp(0.5)+exp(-0.5))/2 1.127626
acos(-0.5) 2.094395
****************/

/***************
ͬ���ͺ���
double asin (double x)//�������x�ķ�����ֵ,x��ΧΪ-1��1֮��,����-PI/2֮PI/2֮��ļ�����
double atan(double x)//�������x�ķ�����ֵ,����-PI/2��PI/2֮��ļ�����
double cos(double x)//�������x ������ֵ,����-1��1֮��ļ�������
double sin(double x)//�������x������ֵ,����-1��1֮��ļ�������
double tan(double x)//�������x������ֵ
***************/

