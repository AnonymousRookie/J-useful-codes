/************************************************************************
* CREATED TIME: 2017-6-10 15:58:44
* LAST MODIFIED TIME: 2017-6-10 15:58:44
* DESCRIPTION: 检测C++编译器的版本是否满足要求
* BY: 357688981@qq.com
************************************************************************/

#ifndef DEFS_H_
#define DEFS_H_


#if defined(_MSC_VER)
#if _MSC_VER < 1900
#error You need to use a C++14 compiler, such as Visual Studio 2015 or higher.
#endif
#else
#if defined(__cplusplus) && (__cplusplus < 201300) // For some reason GCC 4.9 thinks the correct value is 2013000 :(
#error You need to use a C++14 compiler. Try passing -std=c++14 as compiler flag.
#endif
#endif


#endif  // DEFS_H_