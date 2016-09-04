/************************************************************************
* CREATED TIME: 2016-9-4 18:20:55
* LAST MODIFIED TIME: 2016-9-4 19:43:04
* DESCRIPTION: 一些常用的数学计算函数和宏定义
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>

/***********************************
* 常用的宏定义
***********************************/
// 度数 ==> 弧度
/**Util macro for conversion from degrees to radians.*/
#define MATH_DEG_TO_RAD(x)        ((x) * 0.0174532925f)
// 弧度 ==> 度数
/**Util macro for conversion from radians to degrees.*/
#define MATH_RAD_TO_DEG(x)        ((x) * 57.29577951f)

#define MATH_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MATH_MAX(a,b)            (((a) > (b)) ? (a) : (b))

/***********************************
* 常用的函数
***********************************/
/* 001. 返回下一个2的幂值 */
int NextPowerOfTwo(int x);
/** Returns the Next Power of Two value.
Examples:
- If "value" is 15, it will return 16.
- If "value" is 16, it will return 16.
- If "value" is 17, it will return 32.
@param value The value to get next power of two.
@return Returns the next power of two value.
*/
int NextPowerOfTwo(int x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

int main()
{
    // test NextPowerOfTwo()
    std::cout << NextPowerOfTwo(15) << std::endl;
    std::cout << NextPowerOfTwo(32) << std::endl;
    std::cout << NextPowerOfTwo(65) << std::endl;
    return 0;
}