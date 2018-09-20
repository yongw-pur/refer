/*************************
头文件#include <stdlib.h>
int abs(int j);
函数说明:计算参数j的绝对值
返回:j的绝对值的结果

#include<math.h>
double ceil(double x);
函数说明:返回不小于参数x的最小整数值，结果以double形态返回(大于等于x的整数)
返回:不小于参数x的最小整数值(加入lm)

double exp(double x);
函数说明:计算以e为底的x次方值
返回:e的x次方计算结果(加入lm)

double ldexp(double x,int exp);
函数说明:参数x乘上2的exp次方值 3*2^(2) 
float frexp(float x, int *exp);
函数说明:把浮点数x分解成尾数和指数 x=m*2^exp exp为返回的指数

float modf(float num, float *i);
函数说明:将浮点数num分解成整数部分和小数部分
返回:小数部分，将整数部分存入i所指内存中

double log(double x);
函数说明:计算以e为底的x对数值
返回:参数x的自然对数值(加入lm) EDOM 参数x为负数，ERANGE 参数x为零值，零的对数值无定义

double pow(double x,double y);
函数说明:计算以x为底的y次方值
返回:x的y次方计算结果  EDOM 参数x为负数且参数y不是整数

double sqrt(double x);
函数说明:计算参数x的平方根,参数x必须为正数
返回:参数x的平方根值 EDOM 参数x为负数

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
   printf("log(-1) %.8lf\n", log(-1)); //nan, -inf先判断errno，然后输出结果
   printf("log10(100) %.8lf\n", log10(100));
   printf("1.4^2 %.8lf\n", pow(1.4, 2));
   printf("sqrt(3.6) %.8lf\n", sqrt(3.6));
   perror("log failed"); 
   printf("error: %s\n", strerror(errno));
}


/**************
测试结果
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
同类型函数
long labs(long n)  //返回长整型参数n的绝对值
double fabs(double x)  //返回双精度参数x的绝对值    
double cabs(struct complex znum)  
//返回复数znum的绝对值complex.h 
  complex 其实就是一个数组，数组中有两个元素，
  一个表示复数的实部，一个表示复数的虚部
double log10(double x)//计算以10为底的x对数值
gcc -o math math.c -lm
***************/

