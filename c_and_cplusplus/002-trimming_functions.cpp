/************************************************************************
* CREATED TIME: 2016-8-28 20:23:39
* MODIFIED TIME: 2016-8-28 20:23:44
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

// Trimming functions were taken from: http://stackoverflow.com/a/217605

// trim from start
// 去除字符串左端空格
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
// 去除字符串右端空格
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
// 去除字符串两端空格
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}

int main() {
    std::string str = "   Hello World!!!     ";

    std::cout << "[" << str << "]" << std::endl;
    std::cout << "[" << trim(str) << "]" << std::endl;
    std::cout << "[" << str << "]" << std::endl;

    return 0;
}