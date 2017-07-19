/************************************************************************
* CREATED TIME: 2017-7-19 21:35:55
* LAST MODIFIED TIME: 2017-7-19 21:35:55
* DESCRIPTION: 静态/动态链接库
* BY: 357688981@qq.com
************************************************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H


// Set some mandatory defines which are used to select platform implementations
#if !defined(Z_WINDOWS) && !defined(Z_MAC) && !defined(Z_UNIX)
#if defined(_WIN32) || defined(_WIN64)
#define Z_WINDOWS 1
#elif defined(__APPLE__)
#define Z_MAC 1
#else
#define Z_UNIX 1
#endif
#endif


// Symbol visibility. There are two main cases: Building libcalculator and using it
#ifdef BUILDING_LIBCALCULATOR

// Two cases when building: Windows, other platform
#ifdef Z_WINDOWS

// Under Windows we can either use Visual Studio or a proper compiler
#ifdef _MSC_VER
#ifdef DLL_EXPORT
#define Z_PUBLIC_SYMBOL __declspec(dllexport)
#endif
#else
#ifdef DLL_EXPORT
#define Z_PUBLIC_SYMBOL __declspec(dllexport)
#else
#define Z_PUBLIC_SYMBOL __attribute__((visibility("default")))
#define Z_PRIVATE_SYMBOL __attribute__((visibility("hidden")))
#endif
#endif

#else

#define Z_PUBLIC_SYMBOL __attribute__((visibility("default")))
#define Z_PRIVATE_SYMBOL __attribute__((visibility("hidden")))

#endif

#else

// Under MSW it makes a difference whether we use a static library or a DLL
#if defined(Z_WINDOWS) && defined(Z_USING_DLL)
#define Z_PUBLIC_SYMBOL __declspec(dllimport)
#endif

#endif


#ifndef Z_PUBLIC_SYMBOL
#define Z_PUBLIC_SYMBOL
#endif

#ifndef Z_PRIVATE_SYMBOL
#define Z_PRIVATE_SYMBOL
#endif


namespace z {
    class Z_PUBLIC_SYMBOL Calculator {
    public:
        Calculator();
        ~Calculator();
        int add(int a, int b);

        static int m_;
    };


    int Z_PUBLIC_SYMBOL test(int i);
}





#endif  // CALCULATOR_H