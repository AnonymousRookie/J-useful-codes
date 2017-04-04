/************************************************************************
* CREATED TIME: 2017-4-4 16:32:05
* LAST MODIFIED TIME: 2017-4-4 16:32:05
* DESCRIPTION: 命令行参数解析程序配置选项
* BY: 357688981@qq.com
************************************************************************/

#include <boost/program_options.hpp>
#pragma comment(lib, "libboost_program_options-XXX.lib")

/*
命令行参数解析程序配置选项，实现了非常完善的程序配置选项处理功能。

处理程序选项功能的核心类是boost::program_options::options_description，
它的成员函数add_options()重载了括号操作符，用来添加选项解析，用法很像assign库。

在定义了选项参数后，函数store()和parse_command_line()将解析命令行参数串，解析结果保存
在variables_map, 其value_type是boost::any，必须使用as<type>()转型才能获取具体值，
例如: vm["config"].as<std::string>()。
*/

int main(int argc, char** argv) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Help message")
        ("config,c", boost::program_options::value<std::string>()->default_value("../conf/config.xml"), "Set config file")
        ("version,v", "Version info")
        ;

    boost::program_options::variables_map vm;

    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    // 解析完成, 实现选项处理逻辑
    if (vm.count("help")) {  // 处理帮助选项
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("version")) {
        std::cout << "version: " << "v2.0.123" << std::endl;
        return 0;
    }

    if (vm.count("config")) {
        std::string config_file = vm["config"].as<std::string>();
        std::cout << "config_file: " << config_file << std::endl;
        return 0;
    }

    return 0;
}

/*
运行结果：
E:\VS2012_Project\Projects\BoostTest\Debug>BoostTest.exe --help
Allowed options:
  -h [ --help ]                         Help message
  -c [ --config ] arg (=../conf/config.xml)
                                        Set config file
  -v [ --version ]                      Version info

E:\VS2012_Project\Projects\BoostTest\Debug>BoostTest.exe -v
version: v2.0.123

E:\VS2012_Project\Projects\BoostTest\Debug>BoostTest.exe -c="../../../c.xml"
config_file: =../../../c.jaon

E:\VS2012_Project\Projects\BoostTest\Debug>BoostTest.exe -w
unrecognised option '-w'
*/