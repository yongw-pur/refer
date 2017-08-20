/*************************
double strtod(const char *nptr,char **endptr);
函数说明：将字符串转换成浮点数,跳过前面的空格字符，直到遇上数字或正负符
转换成功，转换后的字符串会放在参数buf指针所指的空间。
返回：转换后的浮点型数
#include <stdlib.h>
**************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
   char str[30] = "20.30300";
   char *ptr;
   double ret;

   ret = strtod(str, &ptr);
   
   if(*ptr != '\0')
   {
       printf("the string is not standard type\n"); //str[30] = "20.30300 ABC"; 	
   }
   else
   {
       printf("result is %.2f\n", ret);
   }
   return(0);
}


/**************
测试结果
result is 20.30
****************/

/***************
同类型函数
***************/
