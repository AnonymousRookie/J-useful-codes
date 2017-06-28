/************************************************************************
* CREATED TIME: 2016-8-28 20:46:33
* MODIFIED TIME: 2017-6-28 10:26:35
* DESCRIPTION: Tokenize string
* BY: 357688981@qq.com
************************************************************************/

/**
 * 实现一
 */
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


/**
 * 实现二
 */
#include <iostream>
#include <vector>
#include <string>

namespace z {
    // Tokenizes string. Returns all non-empty substrings
    template<typename String, typename Delim, typename Container = std::vector<String>>
    Container strtok(String const& s, Delim const& delims)
    {
        Container ret;

        typename String::size_type start{}, pos{};
        do {
            pos = s.find_first_of(delims, start);

            // Not found, we're at ends;
            if (pos == String::npos) {
                if (start < s.size()) {
                    ret.emplace_back(s.substr(start));
                }
            }
            else if (pos > start) {
                // Non-empty substring
                ret.emplace_back(s.substr(start, pos - start));
            }
            start = pos + 1;
        } while (pos != String::npos);

        return ret;
    }

}

int main() {

    std::string str = "hello,world,,and,c++...";
    auto v = z::strtok(str, ',');

    for (auto iter = v.cbegin(); iter != v.cend(); ++iter) {
        std::cout << "[" << *iter << "]" << std::endl;
    }
    return 0;
}