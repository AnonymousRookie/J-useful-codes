/************************************************************************
* CREATED TIME: 2017-6-10 14:33:10
* LAST MODIFIED TIME: 2017-6-10 14:33:10
* DESCRIPTION: base64_encode & base64_decode
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
using namespace std;
#include <string>

std::string base64_encode(std::string const& in)
{
    std::string::value_type const base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string ret;

    size_t len = in.size();
    size_t pos{};

    ret.reserve(((len + 2) / 3) * 4);

    while (len >= 3) {
        len -= 3;
        auto const c1 = static_cast<unsigned char>(in[pos++]);
        auto const c2 = static_cast<unsigned char>(in[pos++]);
        auto const c3 = static_cast<unsigned char>(in[pos++]);

        ret += base64_chars[(c1 >> 2) & 0x3fu];
        ret += base64_chars[((c1 & 0x3u) << 4) | ((c2 >> 4) & 0xfu)];
        ret += base64_chars[((c2 & 0xfu) << 2) | ((c3 >> 6) & 0x3u)];
        ret += base64_chars[(c3 & 0x3fu)];
    }
    if (len) {
        auto const c1 = static_cast<unsigned char>(in[pos++]);
        ret += base64_chars[(c1 >> 2) & 0x3fu];
        if (len == 2) {
            auto const c2 = static_cast<unsigned char>(in[pos++]);
            ret += base64_chars[((c1 & 0x3u) << 4) | ((c2 >> 4) & 0xfu)];
            ret += base64_chars[(c2 & 0xfu) << 2];
        }
        else {
            ret += base64_chars[(c1 & 0x3u) << 4];
            ret += '=';
        }
        ret += '=';
    }

    return ret;
}

std::string base64_decode(std::string const& in)
{
    unsigned char const chars[256] =
    {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0xff, 0x80, 0x80, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0x40, 0xff, 0xff,
        0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
        0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    std::string ret;
    ret.reserve((in.size() / 4) * 3);

    size_t pos{};
    size_t len = in.size();

    // Trim trailing whitespace
    while (len && chars[static_cast<unsigned char>(in[len - 1])] == 0x80) {
        --len;
    }

    auto next = [&]() {
        while (pos < len) {
            auto c = chars[static_cast<unsigned char>(in[pos++])];
            if (c != 0x80u) {
                return c;
            }
        }
        return static_cast<unsigned char>(0xffu);
    };

    while (pos < len) {
        auto c1 = next();
        auto c2 = next();
        auto c3 = next();
        auto c4 = next();

        if (c1 == 0xff || c2 == 0xff || c3 == 0xff || c4 == 0xff || c1 == 0x40 || c2 == 0x40) {
            // Bad input
            return std::string();
        }

        if (c4 == 0x40) {
            // Pad
            if (pos < len) {
                // Not at end of string
                return std::string();
            }
            ret += (c1 << 2) | ((c2 >> 4) & 0x3);

            if (c3 != 0x40) {
                ret += ((c2 & 0xf) << 4) | ((c3 >> 2) & 0xf);
            }
        }
        else {
            if (c3 == 0x40) {
                // Bad input
                return std::string();
            }

            ret += (c1 << 2) | ((c2 >> 4) & 0x3);
            ret += ((c2 & 0xf) << 4) | ((c3 >> 2) & 0xf);
            ret += ((c3 & 0x3) << 6) | c4;
        }
    }

    return ret;
}

int main()
{
    std::string str = "hello world";

    std::string enStr = base64_encode(str);

    std::string deStr = base64_decode(enStr);


    std::cout << str << std::endl;

    std::cout << enStr << std::endl;

    std::cout << deStr << std::endl;

    return 0;
}