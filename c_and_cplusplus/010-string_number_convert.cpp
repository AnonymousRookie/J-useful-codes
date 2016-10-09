/************************************************************************
* CREATED TIME: 2016-10-9 17:01:40
* LAST MODIFIED TIME: 2016-10-9 17:01:40
* DESCRIPTION: 数字 字符串 相互转换
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>


const char digits[] = "9876543210123456789";
const char* zero = digits + 9;


// Efficient Integer to String Conversions, by Matthew Wilson.
template<typename T>
size_t convert(char buf[], T value) {
    T i = value;
    char* p = buf;

    do {
        int lsd = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[lsd];
    } while (i != 0);

    if (value < 0) {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

int main() {
    int a = -123;
    char str[32];
    size_t ret = convert(str, a);
    std::cout << str << "\n";  // -123

    return 0;
}