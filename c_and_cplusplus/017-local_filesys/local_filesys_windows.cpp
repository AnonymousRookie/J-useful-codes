/************************************************************************
* CREATED TIME: 2017-7-16 23:01:30
* LAST MODIFIED TIME: 2017-7-16 23:01:30
* DESCRIPTION: local_filesys_windows
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <Windows.h>
using namespace std;

namespace z {

// Determines whether or not provided path exist in current file system
static inline bool pathExists(const char* path, bool considerFile = false) {
    if (path == nullptr) {
        return false;
    }

    DWORD fileType = GetFileAttributesA(path);
    if (fileType == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return considerFile ? true : ((fileType & FILE_ATTRIBUTE_DIRECTORY) == 0 ? false : true);

}


}

int main()
{
    // 检测目录是否存在
    cout << z::pathExists("E:\\Program Files\\Adobe\\哈_哈")<<endl;

    // 检测文件是否存在
    cout << z::pathExists("E:\\Program Files\\Adobe\\哈_哈\\哈_哈.txt", true)<<endl;

    return 0;
}