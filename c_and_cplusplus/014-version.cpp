/************************************************************************
* CREATED TIME: 2017-6-18 20:13:36
* LAST MODIFIED TIME: 2017-6-18 20:13:44
* DESCRIPTION: Macros and functions to get the version of the headers and the library
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <tuple>
#include <string>

// Version string of the library headers
#define XXX_VERSION "0.9.1"

#define XXX_VERSION_MAJOR  0
#define XXX_VERSION_MINOR  9
#define XXX_VERSION_MICRO  1
#define XXX_VERSION_NANO   0

// Suffix string, e.g. "rc1"
#define XXX_VERSION_SUFFIX "0.9.1"


namespace z {
    // Get version string of library
    std::string get_version_string() {
        return XXX_VERSION;
    }
    // Get version of library broken down into components major, minor, micro, nano and suffix
    std::tuple<int, int, int, int, std::string> get_version() {
        return std::make_tuple(XXX_VERSION_MAJOR, XXX_VERSION_MINOR, XXX_VERSION_MICRO, XXX_VERSION_NANO, std::string(XXX_VERSION_SUFFIX));
    }
}


int main() {
    std::cout << z::get_version_string() << std::endl;

    auto version_tuple = z::get_version();
    auto version_tuple_size = std::tuple_size<decltype(version_tuple)>::value;

    std::cout << std::get<0>(version_tuple) << std::endl;
    std::cout << std::get<1>(version_tuple) << std::endl;
    std::cout << std::get<2>(version_tuple) << std::endl;
    std::cout << std::get<3>(version_tuple) << std::endl;
    std::cout << std::get<4>(version_tuple) << std::endl;

    return 0;
}
