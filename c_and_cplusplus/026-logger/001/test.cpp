#include <iostream>
#include "z_logger.h"

int main()
{
    Logger::GetInstance().SetFileBaseName("appname");
    Logger::GetInstance().SetRollSize(10 * 1024 * 1024);  // 10M
    Logger::GetInstance().Start();

    LOG_INFO("info = %d", 1);
    LOG_WARN("warn = %d", 2);
    LOG_ERROR("error = %d", 3);

    return 0;
}
