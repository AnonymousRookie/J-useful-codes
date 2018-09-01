/************************************************************************
* CREATED TIME: 2017-12-12 22:21:16
* LAST MODIFIED TIME: 2017-12-31 17:23:17
* DESCRIPTION: 一些常见的宏定义
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>

/* macro to avoid warnings about unused variables */
#if !defined(UNUSED)
# define UNUSED(x)   ((void)(x))
#endif


// Convert macro to string
#define STRINGIFY(m) #m
#define AS_STRING(m) STRINGIFY(m)


#ifndef MIN
# define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif


#ifndef ARRAY_SIZE
# define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif


#define LOWER(c)            (unsigned char)(c | 0x20)
#define IS_ALPHA(c)         (LOWER(c) >= 'a' && LOWER(c) <= 'z')
#define IS_NUM(c)           ((c) >= '0' && (c) <= '9')
#define IS_ALPHANUM(c)      (IS_ALPHA(c) || IS_NUM(c))
#define IS_HEX(c)           (IS_NUM(c) || (LOWER(c) >= 'a' && LOWER(c) <= 'f'))



int main()
{
    // test AS_STRING
    int nCount = 123;
    std::string str1 = AS_STRING(nCount);
    std::string str2 = AS_STRING(1+2=3);



    return 0;
}