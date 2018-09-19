/*************************
头文件: #include <string.h>
int bcmp(const void *s1, const void *s2, int n);
函数说明:比较字符串s1和s2前n个字符是否相等
返回:如果字符串相等或者n=0，返回0；否则返回非0值澹(1,-1)。不检查NULL(不能传入NULL);

int memcmp(void *s1, void *s2, unsigned int n);
函数说明:比较内存区s1和s2的前n个字节
返回:当s1<s2,返回值-1; 当s1==s2，返回值等于0;当s1>s2时,返回值1
比较大小的依据为:第一个不匹配的字符的值的大小(unsigned char) 不检查NULL(不能传入NULL)

int strcmp(const char *s1,const char *s2);
函数说明:比较参数s1和s2字符串。字符串大小的比较是字符的值。
          strcmp()首先将s1第一个字符值减去s2第一个字符值，若差值为0则再继续比较下个字符，若差值不为0则将差值返回。
          例如字符串"Ac"和"ba"比较则会返回字符"A"(65)和'b'(98)的差值(－33)。
返回:当s1<s2,返回值小于0; 当s1==s2，返回值等于0;当s1>s2时,返回值大于0 (不同的实现返回不同)

int strcasecmp (const char *s1, const char *s2);
函数说明:比较参数s1和s2字符串，比较时会自动忽略大小写的差异。
          strcasecmp()先将字符串转换为小写，然后将s1第一个字符值减去s2第一个字符值
          若差值为0则再继续比较下个字符，若差值不为0则将差值返回。
返回:若参数s1和s2字符串相同则返回0。差值返回。

int strncasecmp(const char *s1,const char *s2,size_t n);
函数说明:比较参数s1和s2字符串前n个字符，比较时会自动忽略大小写的差异
返回值:当s1<s2,返回值-1; 当s1==s2，返回值等于0;当s1>s2时,返回值1
**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char *str1 = "abcdefg";
    char *str2 = "abcde";
    char *str3 = "AbCDE";

    printf("%s bcmp3 %s %d\n", str1, str2, bcmp(str1, str2, 3));
    printf("%s bcmp7 %s %d\n", str1, str2, bcmp(str1, str2, 7));
    //printf("NULL bcmp7 %s %d\n",str2, bcmp(NULL, str2, 7)); core dump
    //printf("NULL memcmp7 %s %d\n",str2, memcmp(NULL, str2, 7));core dump
    //printf("NULL strcmp %s %d\n",str2, strcmp(NULL, str2));core dump
    printf("%s memcmp3 %s %d\n", str1, str2, memcmp(str1, str2, 3));
    printf("%s memcmp7 %s %d\n", str1, str2, memcmp(str1, str2, 7));
    printf("%s strcmp %s %d\n", str1, str2, strcmp(str1, str2));
    printf("%s strcasecmp %s %d\n", str1, str2, strcasecmp(str1, str2)); //返回'f' - 0 
    printf("%s strncasecmp6 %s %d\n", str1, str2, strncasecmp(str1, str2, 10)); 
}

/**************
测试结果
abcdefg bcmp3 abcde 0
abcdefg bcmp7 abcde 1
abcdefg memcmp3 abcde 0
abcdefg memcmp7 abcde 1
abcdefg strcmp abcde 1
abcdefg strcasecmp abcde 102
abcdefg strncasecmp6 abcde 1
****************/

/***************
同类型函数
***************/

