/************************************************************************
* CREATED TIME: 2016-10-9 17:01:40
* LAST MODIFIED TIME: 2017-6-27 17:12:48
* DESCRIPTION: 字符串 转换成 数字
* BY: 357688981@qq.com
************************************************************************/

/**
 * 方法一
 */
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


/**
 * 方法二
 */
#include <iostream>
#include <string>

namespace z {
    // Converts string to integral type T. If string is not convertible, T() is returned.
    template<typename T, typename String>
    T to_integral(String const& s, T const errorval = T())
    {
        T ret{};

        auto it = s.cbegin();
        if (it != s.cend() && (*it == '-' || *it == '+')) {
            ++it;
        }

        if (it == s.cend()) {
            return errorval;
        }

        for (; it != s.cend(); ++it) {
            auto const& c = *it;
            if (c < '0' || c > '9') {
                return errorval;
            }
            ret *= 10;
            ret += c - '0';
        }

        if (!s.empty() && s.front() == '-') {
            return ret *= static_cast<T>(-1);
        }
        else {
            return ret;
        }
    }
}

int main() {
    {
        std::string str = "1234";
        short r = z::to_integral<decltype(r)>(str);
        std::cout << r << std::endl;
    }

    {
        std::string str = "+1234";
        int r = z::to_integral<decltype(r)>(str);
        std::cout << r << std::endl;
    }

    {
        std::string str = "-1234";
        int r = z::to_integral<decltype(r)>(str);
        std::cout << r << std::endl;
    }

    {
        std::string str = "1234abc";
        int r = z::to_integral<decltype(r)>(str);
        if (r == decltype(r)()) {
            std::cout << "string is not convertible!" << std::endl;
        }
        else {
            std::cout << r << std::endl;
        }
    }

    return 0;
}
