/************************************************************************
* CREATED TIME: 2016-9-4 16:46:31
* LAST MODIFIED TIME: 2016-9-4 16:46:31
* DESCRIPTION: 判断字符串是否是数值
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>

bool isStringNumeric(const char* str) {
    if (nullptr == str) {
        std::cout << "nullptr == str" << std::endl;
        return false;
    }
    // The first character may be '-'
    if ('-' == *str) {
        ++str;
    }
    // The first character after the sign must be a digit
    if (!isdigit(*str)) {
        return false;
    }
    ++str;
    // All remaining characters must be digits, with a single decimal (.) permitted
    unsigned int decimalCount = 0;
    while (*str) {
        if (!isdigit(*str)) {
            if ('.' == *str && 0 == decimalCount) {
                // Max of 1 decimal allowed
                ++decimalCount;
            } else {
                return false;
            }
        }
        ++str;
    }
    return true;
}

int main() {
    char str[32] = "-1244.6547000";
    std::cout << isStringNumeric(str) << std::endl;
    return 0;
}