/*************************
double strtod(const char *nptr,char **endptr);
����˵�������ַ���ת���ɸ�����,����ǰ��Ŀո��ַ���ֱ���������ֻ�������
ת���ɹ���ת������ַ�������ڲ���bufָ����ָ�Ŀռ䡣
���أ�ת����ĸ�������
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
���Խ��
result is 20.30
****************/

/***************
ͬ���ͺ���
***************/
