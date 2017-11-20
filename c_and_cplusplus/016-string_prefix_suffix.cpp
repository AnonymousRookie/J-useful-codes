/************************************************************************
* CREATED TIME: 2017-7-16 12:37:35
* LAST MODIFIED TIME: 2017-11-20 22:42:50
* DESCRIPTION: 检测字符串是否以某个前缀开头或以某个后缀结尾
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

// 实现1
namespace z1 {

    // ----------------------------------------------------------------------
    // HasPrefixString()
    //    Check if a string begins with a given prefix.
    // StripPrefixString()
    //    Given a string and a putative prefix, returns the string minus the
    //    prefix string if the prefix matches, otherwise the original
    //    string.
    // ----------------------------------------------------------------------
    inline bool HasPrefixString(const string& str,
        const string& prefix) {
            return str.size() >= prefix.size() &&
                str.compare(0, prefix.size(), prefix) == 0;
    }

    inline string StripPrefixString(const string& str, const string& prefix) {
        if (HasPrefixString(str, prefix)) {
            return str.substr(prefix.size());
        } else {
            return str;
        }
    }

    // ----------------------------------------------------------------------
    // HasSuffixString()
    //    Return true if str ends in suffix.
    // StripSuffixString()
    //    Given a string and a putative suffix, returns the string minus the
    //    suffix string if the suffix matches, otherwise the original
    //    string.
    // ----------------------------------------------------------------------
    inline bool HasSuffixString(const string& str,
        const string& suffix) {
            return str.size() >= suffix.size() &&
                str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    inline string StripSuffixString(const string& str, const string& suffix) {
        if (HasSuffixString(str, suffix)) {
            return str.substr(0, str.size() - suffix.size());
        } else {
            return str;
        }
    }

}

// 实现2
namespace z2 {
    bool starts_with(const char* str, const char* pattern) {
        if (!str || !pattern) {
            return false;
        }
        while (*pattern && *str == *pattern) {
            ++str;
            ++pattern;
        }
        return (*pattern == 0);
    }
}


int main()
{
    cout << z1::HasPrefixString("cplusplus.pdf", "cplus") << endl;  // 1
    cout << z1::StripPrefixString("cplusplus.pdf", "cplus") << endl;// plus.pdf

    cout << z1::HasSuffixString("cplusplus.pdf", ".pdf") << endl;   // 1
    cout << z1::StripSuffixString("cplusplus.pdf", ".pdf") << endl; // cplusplus

    return 0;
}