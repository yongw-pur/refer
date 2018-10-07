/*************************
头文件
#define _XOPEN_SOURCE
#include<unistd.h>
char *crypt(const char *key, const char *salt)
函数说明:crypt()将使用Data Encryption Standard(DES)演算法将参数key所指的字符串加以编码，
         key字符串长度仅取前8个字符，超过此长度的字符没有意义。参数salt为两个字符组成的字符串，由a-z、A-Z、0-9，"."和"/"所组成，
         用来决定使用4096种不同内建表格的哪一个。函数执行成功后会返回指向编码过的字符串指针
         参数key 所指的字符串不会有所更动。编码过的字符串长度为13个字符，前两个字符为参数salt代表的字符串
返回:密码字符串 //使用GCC编译时需加-lcrypt

#include<stdlib.h>
void *bsearch(const void *key,const void *base,size_t nmemb,size_tsize,int (*compar) (const void*,const void*))
函数说明:利用二元搜索从排序好的数组中查找数据。
         参数key指向欲查找的关键数据，参数base指向要被搜索的数组开头地址，参数nmemb代表数组中的元素数量，每一元素的大小则由参数size决定
         参数compar为一函数指针，这个函数用来判断两个元素之间的大小关系，若传给compar的第一个参数所指的元素数据大于第二个参数所指的元素数据则必须回传大于0的值，两个元素数据相等则回传0。
返回:找到关键数据则返回找到的地址，如果在数组中找不到关键数据则返回NULL

void qsort(void * base,size_t nmemb,size_t size,int ( * compar)(const void *, const void *))
函数说明:参数base指向欲排序的数组开头地址，参数nmemb代表数组中的元素数量，每一元素的大小则由参数size决定
         参数compar为一函数指针，这个函数用来判断两个元素间的大小关系，若传给compar的第一个参数所指的元素数据大于第二个参数所指的元素数据则必须回传大于零的值，两个元素数据相等则回传0

void srand (unsigned int seed)
函数说明:设置rand()产生随机数时的随机数种子。参数seed必须是个整数，通常可以利用geypid()或time(0)的返回值来当做seed。如果每次seed都设相同值，rand()所产生的随机数值每次就会一样

int rand(void)
函数说明:返回一随机数值，范围在0至RAND_MAX 间。
         在调用此函数产生随机数前，必须先利用srand()设好随机数种子,如果未设随机数种子，rand()在调用时会自动设随机数种子为1
返回: 0至RAND_MAX之间的随机数值，RAND_MAX定义在stdlib.h，其值为2147483647
该函数为非线程安全函数。并且生成随机数的性能不是很好，已经不推荐使用

**************************/
#define _XOPEN_SOURCE //否则会有返回值为int类型的warning提醒
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int compare(const void *a,const void *b)//
{
    return *(int *)a - *(int *)b; //小到大
    //return *(int *)b - *(int *)a; //大到小
}

main()
{
    char passwd[13];
    char *key;
    char slat[2];
    key= getpass("Input First Password:");
    slat[0]=key[0]; //slat可以任意
    slat[1]=key[1];
    strcpy(passwd, crypt(key, slat));
    printf("After crypt(),1st passwd :%s\n", passwd);

    int i = 9;
    int index;
    int *p;
    //int array[]={1,4,5,6,9,11}; // a - b
    //int array[]={20,9,8,3,2,1}; //b - a

    int array[]={5,6,3,17,9,2};
    qsort(array, sizeof(array)/sizeof(int), sizeof(int), compare);
    for (index = 0; index < sizeof(array)/sizeof(int); index++)
        printf("array[%d] %d\n",index, array[index]);
    p = (int *)bsearch(&i, array, sizeof(array)/sizeof(int), sizeof(int), compare);
    printf("bsearch data %d\n", *p);

    
    int j;
    srand((int)time(0));
    for(j = 0; j < 10; j++)
    {
        printf(" %d ", 1+(int)(10.0*rand()/(RAND_MAX+1.0)));
    }
}



/**************
测试结果
****************/

/***************
同类型函数:
void *lfind (const void *key,const void *base,size_t *nmemb,size_t size,int(* compar) (const void * ,const void *))
线性查找，compare来判断两个元素是否相同，若传给compar的异地个参数所指的元素数据和第二个参数所指的元素数据相同时则返回0，两个元素数据不相同则返回非0值。当找不到关键数据时lfind()返回NULL

void *lsearch(const void * key ,const void * base ,size_t * nmemb,size_t size, int ( * compar) (const void * ,const void *))
lsearch()当找不到关键数据时会主动把该笔数据加入数组尾端

void srandom(unsigned int seed)设置种子值，一般与“当前时间 + 进程ID”作为种子，如果没用调用该函数，则通过random返回的默认种子值为1
long int random(void) 0-RAND_MAX 之间的一个 long 类型整数，该函数会产生一个非常大的随机值（推荐使用)
***************/

