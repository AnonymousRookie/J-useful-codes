/************************************************************************
* CREATED TIME: 2016-9-11 12:58:25
* LAST MODIFIED TIME: 2016-9-11 12:58:25
* DESCRIPTION: 字符串转换成 全部小写/全部大写
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>

std::string& InPlaceLowercase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

std::string& InPlaceUppercase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

std::string StrToLower(const std::string& s) {
    std::string res(s);
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

std::string StrToUpper(const std::string& s) {
    std::string res(s);
    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}

int main() {
    std::string str = "AfiFNInieg MIF893huHFU";
    std::cout << InPlaceLowercase(str) << std::endl;
    std::cout << str << std::endl;

    str = "AfiFNInieg MIF893huHFU";
    std::cout << InPlaceUppercase(str) << std::endl;
    std::cout << str << std::endl;

    str = "AfiFNInieg MIF893huHFU";
    std::cout << StrToLower(str) << std::endl;
    std::cout << str << std::endl;

    str = "AfiFNInieg MIF893huHFU";
    std::cout << StrToUpper(str) << std::endl;
    std::cout << str << std::endl;

    return 0;
}