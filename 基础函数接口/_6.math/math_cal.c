/*************************
ͷ�ļ�#include <stdlib.h>
int abs(int j);
����˵��:�������j�ľ���ֵ
����:j�ľ���ֵ�Ľ��

#include<math.h>
double ceil(double x);
����˵��:���ز�С�ڲ���x����С����ֵ�������double��̬����(���ڵ���x������)
����:��С�ڲ���x����С����ֵ(����lm)

double exp(double x);
����˵��:������eΪ�׵�x�η�ֵ
����:e��x�η�������(����lm)

double ldexp(double x,int exp);
����˵��:����x����2��exp�η�ֵ 3*2^(2) 
float frexp(float x, int *exp);
����˵��:�Ѹ�����x�ֽ��β����ָ�� x=m*2^exp expΪ���ص�ָ��

float modf(float num, float *i);
����˵��:��������num�ֽ���������ֺ�С������
����:С�����֣����������ִ���i��ָ�ڴ���

double log(double x);
����˵��:������eΪ�׵�x����ֵ
����:����x����Ȼ����ֵ(����lm) EDOM ����xΪ������ERANGE ����xΪ��ֵ����Ķ���ֵ�޶���

double pow(double x,double y);
����˵��:������xΪ�׵�y�η�ֵ
����:x��y�η�������  EDOM ����xΪ�����Ҳ���y��������

double sqrt(double x);
����˵��:�������x��ƽ����,����x����Ϊ����
����:����x��ƽ����ֵ EDOM ����xΪ����

**************************/
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>//strerror
#include <errno.h> //errno
//#include <complex.h>

int main()
{
    int b = -100;
    errno = 0;
    /*complex  double  a = 3.0 + 4.0 * _Complex_I;
    __complex__ double b = 4.0 + 5.0 * _Complex_I;
    _Complex  double c = 5.0 + 6.0 * _Complex_I;

    printf("a=%f+%fi\n", creal(a),cimag(a));
    printf("b=%f+%fi\n", creal(b), cimag(b));
    printf("c=%f+%fi\n", creal(c), cimag(c));

    double x, i;
    x=modf(-74.12,&i);
    printf("-74.12=%.0lf+(%.2lf)",i,x);*/

   printf("abs(-100) %d\n", abs(-100));
   printf("ceil(-100) %lf\n", ceil(-100));
   printf("exp(2) %.8lf\n", exp(2));
   printf("log(-1) %.8lf\n", log(-1)); //nan, -inf���ж�errno��Ȼ��������
   printf("log10(100) %.8lf\n", log10(100));
   printf("1.4^2 %.8lf\n", pow(1.4, 2));
   printf("sqrt(3.6) %.8lf\n", sqrt(3.6));
   perror("log failed"); 
   printf("error: %s\n", strerror(errno));
}


/**************
���Խ��
abs(-100) 100
ceil(-100) -100.000000
exp(2) 7.38905610
log(-1) nan
log10(100) 2.00000000
1.4^2 1.96000000
sqrt(3.6) 1.897366596
log failed: Numerical argument out of domain
error: Numerical argument out of domain
****************/

/***************
ͬ���ͺ���
long labs(long n)  //���س����Ͳ���n�ľ���ֵ
double fabs(double x)  //����˫���Ȳ���x�ľ���ֵ    
double cabs(struct complex znum)  
//���ظ���znum�ľ���ֵcomplex.h 
  complex ��ʵ����һ�����飬������������Ԫ�أ�
  һ����ʾ������ʵ����һ����ʾ�������鲿
double log10(double x)//������10Ϊ�׵�x����ֵ
gcc -o math math.c -lm
***************/

