/************************************************************************
* CREATED TIME: 2016-8-28 15:43:33
* MODIFIED TIME: 2017-12-29 22:47:27
* DESCRIPTION: SplitFilename, GetDirName
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <string>

// "C:\\Program Files\\STSLIST.DLL" ==> "STSLIST.DLL"
static void SplitFilename(std::string& str) {
    size_t found = 0;
    /*
        size_t: 于机器的环境, 它的长度有可能不同, 它是一个与机器相关的unsigned类型,
        其大小足以保证存储内存中对象的大小。
        当find找不到所要找的字符的时候, 它返回的是npos的值, 这个值是与size_t相关的。
        假如, 你是用 string s; int rc = s.find(.....); 然后判断，if ( rc == string::npos )
        这样在不同的机器平台上表现就不一样了。如果, 你的平台的string::size_t的长度正好和int相匹配,
        那么这个判断会侥幸正确。但换成另外的平台, 有可能 string::size_t的类型是64位长度的,
        那么判断就完全不正确了。 所以, 正确的应该是: string::size_t rc = s.find(.....);
        这个时候使用 if ( rc == string::npos )就正确了。
    */
    found = str.find_last_of("/\\");
    if (found != std::string::npos) {
        str = str.substr(found + 1);
    }
}

// "C:\\Program Files\\STSLIST.DLL" ==> "C:\\Program Files\\"
// Assume a filename, and not a directory name like "/foo/bar/"
static std::string GetDirName(const std::string& filename) {
    size_t found = filename.find_last_of("/\\");
    if (found == std::string::npos) {
        return "";
    } else {
        return filename.substr(0, found);
    }
}

int main()
{
    std::string str = "C:\\Program Files\\Office12\\STSLIST.DLL";
    SplitFilename(str);
    std::cout << str <<std::endl;  // STSLIST.DLL
    printf("%s\n", str.c_str());
	return 0;
}