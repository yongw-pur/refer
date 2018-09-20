/*************************
#include<math.h>
double acos (double x);
函数说明:计算参数x的反余弦值,参数x范围为-1至1
返回:返回0至PI之间的计算结果，单位为弧度，在函数库中角度均以弧度来表示 EDOM参数x超出范围

double atan2(double y,double x);
函数说明:计算参数y/x的反正切值
返回:-PI/2 至PI/2 之间的计算结果(加入lm)

double cosh(double x);
函数说明:计算参数x的双曲线余玄值;数学定义式为:(exp(x)+exp(-x))/2。
返回:参数x的双曲线余玄值

double sinh( double x);
函数说明:计算参数x的双曲线正玄值,数学定义式为:(exp(x)-exp(-x))/2。
返回:参数x的双曲线正玄值

double tanh(double x);
函数说明:计算参数x的双曲线正切值,数学定义式为:sinh(x)/cosh(x)
返回:参数x的双曲线正切值

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
测试结果
cosh(0.5) 1.127626
(exp(0.5)+exp(-0.5))/2 1.127626
acos(-0.5) 2.094395
****************/

/***************
同类型函数
double asin (double x)//计算参数x的反正弦值,x范围为-1至1之间,返回-PI/2之PI/2之间的计算结果
double atan(double x)//计算参数x的反正切值,返回-PI/2至PI/2之间的计算结果
double cos(double x)//计算参数x 的余玄值,返回-1至1之间的计算结果。
double sin(double x)//计算参数x的正玄值,返回-1至1之间的计算结果。
double tan(double x)//计算参数x的正切值
***************/

