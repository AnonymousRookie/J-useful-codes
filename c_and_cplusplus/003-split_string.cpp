/************************************************************************
* CREATED TIME: 2016-8-28 20:46:33
* MODIFIED TIME: 2016-8-28 20:46:37
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


// 按指定分隔符对字符串进行split
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main(){
    std::string str = "hello,world! hello, C++";
    std::cout << "[" << str << "]" << std::endl;

    std::vector<std::string> ret = split(str, ',');
    for(auto iter = ret.begin(); iter != ret.end(); ++iter) {
        std::cout << "[" << *iter << "]" << std::endl;
    }

    return 0;
}
