## Windows、Linux、MacOS三个系统中，文本的换行符格式不同。编写一个换行符格式转换工具，实现三个系统间的换行符格式的转换。

**Usage:** .\line_ending_converter.exe <input_file> <output_flie> < system >

**system option:** Windows, Linux, macOS

***

# 1. main.c

main.c 文件包含程序的入口点 main 函数，负责解析命令行参数并调用相应的功能函数来处理文件或目录的转换。

作用：
解析命令行参数，确定输入路径、输出路径和新的换行符类型。
根据输入路径的类型（文件或目录），调用相应的处理函数来处理文件或递归处理目录。


# 2. arg_parser.c / arg_parser.h

arg_parser.c 和 arg_parser.h 文件定义了命令行参数解析的相关功能函数和数据结构。

作用：
parse_arguments 函数：解析命令行参数，获取输入路径、输出路径和新的换行符类型。
确保命令行参数的正确性，如路径是否合法，新的换行符类型是否有效。
# 3. file_utils.c / file_utils.h

file_utils.c 和 file_utils.h 文件提供了文件和目录处理的辅助函数，如判断文件类型、处理隐藏文件或系统文件等。

作用：
is_hidden_or_system_file：判断是否为隐藏文件或系统文件。
is_hidden_or_system_dir：判断是否为隐藏或系统目录。
is_directory：判断路径是否为目录。
# 4. line_ending_converter.c / line_ending_converter.h

line_ending_converter.c 和 line_ending_converter.h 文件定义了换行符转换的功能函数和相关常量。

作用：
convert_line_endings 函数：将源文件中的换行符统一转换为指定的新的换行符类型（如 Windows 的 \r\n 或 Unix 的 \n）。
定义了 WINDOWS_EOL 和 UNIX_EOL 常量，分别表示 Windows 和 Unix/Linux 系统的换行符。
# 5. file_processor.c/file_processor.h

file_processor.c 和 file_processor.h文件包含了处理文件和目录的具体逻辑，如打开文件、转换换行符、处理目录等。

作用：
process_file 函数：处理单个文件，包括打开文件、转换换行符、关闭文件等操作。
process_directory 函数：递归处理目录，包括遍历目录下的文件和子目录，并调用 process_file 或自身来处理文件或递归处理子目录。

***

- [x] 使用C语言编写应用程序，实现Windows、Linux、MacOS系统间的换行符格式转换。
- [x] 除换行符格式外，原文件中的文件内容不能改变。
- [x] 支持的文件格式包括.txt、.c、.cpp、.h、.hpp、Makefile、.log等纯文本格式。
- [x] 系统和隐藏目录和文件应忽略，如System32、.svn、.ssh、.gitconfig等。
- [x] 编写软件结构图、流程图，测试报告以及必要的使用说明（ReleaseNote）。
- [x] 应自行编写应用程序，禁止抄袭或在程序中直接调用三方软件实现该功能。
- [x] 应进行适当的函数封装，各函数/模块应遵循高内聚低耦合的设计原则。
- [x] 统一的编码格式和规范，代码整洁、美观、可读性高。
- [x] 支持批量（目录/子目录）转换。
- [x] 转换结束后，生成统计报告（包括源/目标文件全路径，转换前后的换行符格式，转换过程的执行结果[已转换/不需要转换/不支持的文件格式/错误]，耗时等信息）。
- [x] 基于模块化的设计，实现转换业务和系统平台分离，达到跨平台目的，即该程序可以在Windows（vs）和Ubuntu（gcc）上编译和运行。
