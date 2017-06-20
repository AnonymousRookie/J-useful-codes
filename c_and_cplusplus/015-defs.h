/************************************************************************
* CREATED TIME: 2016-8-27 23:03:56
* LAST MODIFIED TIME: 2016-8-28 09:53:17
* DESCRIPTION: 跨平台宏定义
* BY: 357688981@qq.com
************************************************************************/

#ifndef TIME_H
#define TIME_H

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

#endif  // TIME_H
