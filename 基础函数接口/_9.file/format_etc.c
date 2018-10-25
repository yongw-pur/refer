/*************************
头文件
#include<stdio.h>
int fprintf(FILE *stream, const char *format,...)
函数说明:根据参数format字符串转换并格式化数据，将结果输出到stream指定的文件中，直到出现字符串结束('\0')
返回:成功则返回实际输出的字符数，失败则返回-1

int fscanf(FILE * stream ,const char *format,....)
函数说明:从stream的文件流中读取字符串，再根据参数format字符串来转换并格式化数据
返回:成功则返回参数数目，失败则返回-1

int printf(const char *format,...)
函数说明:根据参数format字符串来转换并格式化数据，然后将结果写出到标准输出设备，直到出现字符串结束('\0')为止
         格式化形式:％(flags)(width)(.prec)type
         type的几种形式
            ％d 整数的参数会被转成一有符号的十进制数字
            ％u 整数的参数会被转成一无符号的十进制数字
            ％o 整数的参数会被转成一无符号的八进制数字
            ％x 整数的参数会被转成一无符号的十六进制数字，并以小写abcdef表示
            ％X 整数的参数会被转成一无符号的十六进制数字，并以大写ABCDEF表示浮点型数
            ％f double 型的参数会被转成十进制数字，并取到小数点以下六位，四舍五入。
            ％e double型的参数以指数形式打印，有一个数字会在小数点前，六位数字在小数点后，而在指数部分会以小写的e来表示。
            ％E 与％e作用相同，唯一区别是指数部分将以大写的E 来表示。
            ％g double 型的参数会自动选择以％f 或％e 的格式来打印，其标准是根据欲打印的数值及所设置的有效位数来决定。
            ％G 与％g 作用相同，唯一区别在以指数形态打印时会选择％E 格式。
            ％c 整型数的参数会被转成unsigned char型打印出。
            ％s 指向字符串的参数会被逐字输出，直到出现NULL字符为止
            ％p 如果是参数是"void *"型指针则使用十六进制格式显示
          prec的几种情况:
            正整数最小位数
            浮点型数中代表小数位数
            在％g 格式代表有效位数的最大值
            在％s格式代表字符串的最大长度
            若为x符号则代表下个参数值为最大长度
          width为参数的最小长度，若此栏并非数值，而是*符号，则表示以下一个参数当做参数长度
          flags几种情况:
            + 一般在打印负数时，printf会加印一个负号，整数则不加任何负号。此旗标会使得在打印正数前多一个正号（+）
            # 此旗标根据其后转换字符的不同而有不同含义。当在类型为o 之前（如％#o），则会在打印八进制数值前多印一个o
              在类型为x之前（％#x）则会在打印十六进制数前多印'0x'，在型态为e、E、f、g或G之前则会强迫数值打印小数点。
              在类型为g或G之前时则同时保留小数点及小数位数末尾的零
            0 当有指定参数时,无数字的参数将补上0。默认是关闭此旗标，所以一般会打印出空白字符(仅限数值)
            - 左对齐
返回:成功则返回实际输出的字符数，失败则返回-1

int scanf(const char *format,...)
函数说明:将输入的数据根据参数format字符串来转换并格式化数据
         格式化形式:％[*][size][l][h]type
         * 代表该对应的参数数据忽略不保存
         size 为允许参数输入的数据长度。
         l 输入的数据数值以long int 或double型保存。
         h 输入的数据数值以short int 型保存
         type的几种形式
         ％d 输入的数据会被转成一有符号的十进制数字(int),无法识别0x的输入
         ％i 输入的数据会被转成一有符号的十进制数字，若输入数据以"0x"或"0X"开头代表转换十六进制数字，若以"0"开头则转换八进制数字，其他情况代表十进制。
         ％o 输入的数据会被转换成一无符号的八进制数字。
         ％u 输入的数据会被转换成一无符号的正整数。
         ％x ％X输入的数据为无符号的十六进制数字，转换后存于unsigned int型变量。
         ％f ％e ％E ％g输入的数据为有符号的浮点型数，转换后存于float型变量。
         ％s 输入数据为以空格字符为终止的字符串。
         ％c 输入数据为单一字符。
         [] 读取数据但只允许括号内的字符。如[a-z]。
         [^] 读取数据但不允许中括号的^符号后的字符出现，如[^0-9]

头文件
#include<stdio.h>
#include<stdarg.h>
int vprintf(const char *format,va_list ap)
函数说明:vprintf作用和printf相同,va_list为不定个数的参数列
返回:成功则返回实际输出的字符数，失败则返回-1. 用来实现自己的输出函数

int vscanf( const char * format,va_list ap)
函数说明:将输入的数据根据参数format字符串来转换并格式化数据
返回:成功则返回参数数目，失败则返回-1

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
函数说明:将可变参数格式化输出到一个字符数组,str输出到的数组，size指定大小，防止越界，format格式化参数

int snprintf(char*str, size_t size,constchar*format, ...)
函数说明:最多从源串中拷贝size-1个字符到目标串中，然后再在后面加一个0,size为最大的限制
        如果size-1大于等于字串的长度,则把字串都拷贝到dst
        如果size-1小于字串的长度,则从字串拷贝size-1长度的字符串到dst，并且末尾置\0
        一般size使用sizeof获取空间的最大长度
返回:欲写入的字符串(即源字符串)长度(strlen)，而不是实际写入的字符串度,失败则返回-1

**************************/
#include<stdio.h>
#include<stdarg.h>

int my_scanf(const char *format, ...)
{
    va_list ap;
    int retval;
    va_start(ap, format);
    retval = vscanf(format,ap);
    va_end(ap);
    return retval;
}

int my_printf(const char *format, ...)
{
    va_list ap;
    int retval;
    va_start(ap, format);
    retval = vprintf(format,ap);
    va_end(ap);
    return retval;
}

void main()
{
    int m;
    unsigned int n;
    char s[5];
    int i = 150;
    int j = -100;
    double k = 3.14159;
    fprintf(stdout,"hello world %d %f %x \n",j,k,i);
    fprintf(stdout,"%2d %*d\n",i, 2, i);//%*d告诉printf函数将要使用是一个可变的字段宽度，字段宽度由第一个参数指定，即用2代替

    //fscanf(stdin,"%d %x %5[a-z] %*s %f",&m,&n,s,s); //输入10 0x1b aaaaaaaaa bbbbbbbbbb
    //printf("%d %d %s \n",m,n,s);

    printf("%-10d\n", 234); //左对齐
    printf("%010d\n", 234); //左侧补0
    my_scanf("%i", &m);
    my_printf("my scanf %d\n", m);
}

/**************
测试结果
hello world -100 3.141590 96 
150 150
10 0x1b aaaaaaaaa bbbbbbbbbb //input
10 27 aaaaa
234       
0000000234
0x14 //input
my scanf 20
****************/

/***************
同类型函数:(函数区别在于格式化数据的来源 v:valist方式，f:文件方式，s:字串保存, n:带长度限制)
int vsprintf(char * str,const char * format,va_list ap)//根据参数format字符串来转换并格式化数据，然后将结果复制到参数str所指的字符串数组，直到出现字符串结束('\0')为止，sprintf内部调用方法
int vsscanf(const char * str,const char * format,va_list ap)//将参数str的字符串根据参数format字符串来转换并格式化数据，sscanf
int sprintf( char *str,const char *format,...)//根据参数format字符串来转换并格式化数据，然后将结果复制到参数str所指的字符串数组，直到出现字符串结束('\0')为止
           成功则返回参数str字符串长度，失败则返回-1，错误原因存于errno中。使用此函数得留意堆栈溢出，或改用snprintf
int sscanf (const char *str, const char *format,...)//将参数str的字符串根据参数format字符串来转换并格式化数据,成功则返回参数数目，失败则返回-1
int vfprintf(FILE *stream, const char *format,va_list ap)//根据参数format字符串来转换并格式化数据，然后将结果输出到参数stream指定的文件中，直到出现字符串结束('\0')为止vprintf()
int vfscanf(FILE *stream,  const char *format ,va_list ap)//从参数stream 的文件流中读取字符串，再根据参数format字符串来转换并格式化数据(stdin)
           从文件中读取数据，根据格式化的方法，填充到后面的参数列表m,n
***************/

