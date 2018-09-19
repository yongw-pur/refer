/*************************
头文件: #include <string.h>
查找到的包含在内
char *index( const char *s, int c);
函数说明:找出参数s字符串中第一个出现的参数c地址，然后将该字符出现的地址返回。
         字符串结束字符(NULL)也视为字符串一部分,也能搜索.(以0为搜索的结束)
返回:如果找到指定的字符则返回该字符所在地址，否则返回0

void *memchr(const void *s,int c,size_t n);
函数说明:从头开始搜寻s所指的内存内容前n个字节，直到发现第一个值为c的字节，则返回指向该字节的指针。
         (以n为搜索的结束，字符串中有两个0，也能搜索，注意不能超过s的范围)
返回:如果找到指定的字节则返回该字节的指针，否则返回0

char * rindex( const char *s,int c);
函数说明:找出参数s字符串中最后一个出现的参数c地址，然后将该字符出现的地址返回。
         strlen给定字符串的长度, 字符串结束字符(NULL)也视为字符串一部分
返回:如果找到指定的字符则返回该字符所在的地址，否则返回0

char * strchr (const char *s,int c);
函数说明:找出参数s字符串中第一个出现的参数c地址，然后将该字符出现的地址返回。
返回:如果找到指定的字符则返回该字符所在地址，否则返回0。

char * strrchr(const char *s, int c);
函数说明:找出参数s字符串中最后一个出现的参数c地址，然后将该字符出现的地址返回
返回:如果找到指定的字符则返回该字符所在地址，否则返回0

char *strpbrk(const char *s,const char *accept);
函数说明:找出参数s 字符串中最先出现存在参数accept字符串中的任意字符。
返回: 如果找到指定的字符则返回该字符所在地址，否则返回0。(s中是否存在accpet中的字符)

size_t strspn (const char *s,const char *accept);
函数说明:从参数s 字符串的开头计算连续的字符，而这些字符都完全是accept 所指字符串中的字符。
         若strspn()返回的数值为n，则代表字符串s 开头连续有n个字符都是属于字符串accept内的字符
         第一个不在accpet中的位置
返回:字符串s开头连续包含字符串accept内的字符数目(0没有) s[index]为不属于accpet的第一个元素。包含0进行比较

char *strstr(const char *s,const char *key);
函数说明:从字符串s中搜寻字符串key，并将第一次出现的地址返回
返回:指定字符串第一次出现的地址，否则返回0.key中第一个字符的位置

char *strtok(char *s,const char *delim);
函数说明:将字符串分割成一个个片段。参数s指向欲分割的字符串，参数delim则为分割字符串
         当strtok()在参数s的字符串中发现到参数delim的分割字符时则会将该字符改为\0 字符。
         在第一次调用时，strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。
         每次调用成功则返回下一个分割后的字符串指针(静态指针保存下一个数据的位置)
返回:下一个分割后的字符串指针，如果已无从分割则返回NULL

char *strsep(char **stringp, const char *delim);
函数说明:字符串为一组字符串。从stringp指向的位置起向后扫描，遇到delim指向的字符串中的字符后，将此字符替换为NULL，返回stringp指向的地址。
         适用于分割“关键字”在两个字符串之间只“严格出现一次”的情况
         如果“关键字”在字符串之间连续出现, *key_point == 0的时候continue
返回:下一个分割后的字符串指针，如果已无从分割则返回NULL

**************************/
#include <stdio.h>
#include <string.h>
main()
{
    char *p;
    int count;
    char s[] ="0123456789012345678901234567890";
    //s[6] = 0;
    
    p = index(s,'9');
    p = rindex(s,'9');
    p = strchr(s, '9');
    p = memchr(s,'9', 100);
    p= strpbrk(s,"4398");/*3 会最先在s 字符串中找到*/
    count = strspn(s, "0123456789012345678901234567890");
    p = strstr(s, "23");
    printf("%s %d\n", p, count);

    
    char s1[]="ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    char *delim="-: ";
    char *q;
	for(q = strtok(s1, delim); q != NULL; q = strtok(NULL, delim)) {
		printf("token %s\n", q);
	}
    printf("\n");
    /*printf("%s ", strtok(s1,delim));
    while((q=strtok(NULL,delim)))
        printf("%s ",q);*/

    char source[] = "hello, world! welcome to china!";
	char delim2[] = " ,!";
 
	char *s2 = source; //不能直接使用数组地址，数组地址不能修改
	char *token;
	for(token = strsep(&s2, delim2); token != NULL; token = strsep(&s2, delim2)) 
    {
        if (*token == 0) //解决多个delim在一起的情况
            continue;
        printf("token %s\n", token);
	}
}

/**************
测试结果
23456789012345678901234567890 31
token ab
token cd
token ef;gh
token i
token jkl;mnop;qrs
token tu
token vwx
token y;z

token hello
token world
token welcome
token to
token china
****************/

/***************
说明:
strtok, strsep:
如果输入的串的有连续的多个字符属于delim,strtok会返回NULL，而strsep会返回空串""。
因而如果想用strsep函数分割字符串必须进行返回值是否是空串的判断。
程序中最好尽量避免使用strtok，转而使用速度更快strsep。
***************/

