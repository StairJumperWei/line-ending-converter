## Windows、Linux、MacOS三个系统中，文本的换行符格式不同。编写一个换行符格式转换工具，实现三个系统间的换行符格式的转换。

**Usage:** .\line_ending_converter.exe <input_file> <output_flie> < system >

**system option:** Windows, Linux, macOS


# arg_parser.h / arg_parser.c
**作用：** 解析命令行参数。

**具体实现：** 提供了 parse_arguments 函数，用于解析命令行传入的参数，包括输入路径、输出路径以及新的行结束符类型（Windows 或 Unix[Linux\macOS]）。

# file_utils.h / file_utils.c
**作用：** 提供文件和目录相关的实用函数。

**具体实现：** 包括判断文件是否为隐藏或系统文件 (is_hidden_or_system_file)，判断路径是否为隐藏或系统目录 (is_hidden_or_system_dir)，以及判断路径是否为目录 (is_directory)。

# line_ending_converter.h / line_ending_converter.c
**作用：** 提供行结束符转换功能。

**具体实现：** 定义了 Windows 和 Unix 的行结束符常量，并提供了 convert_line_endings 函数，用于将源文件中的行结束符转换为指定的新行结束符类型。

# file_processor.h / file_processor.c
**作用：** 处理文件和目录的转换任务。

**具体实现：** 包括处理单个文件的转换 (process_file) 和处理整个目录的递归转换 (process_directory)。

# main.c
**作用：** 程序的入口点，调用其他模块完成整体文件和目录的转换工作。


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
- [ ] 基于模块化的设计，实现转换业务和系统平台分离，达到跨平台目的，即该程序可以在Windows（vs）和Ubuntu（gcc）上编译和运行。
