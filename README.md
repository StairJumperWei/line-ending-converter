# 使用说明
## 功能介绍
- 支持在不同操作系统上运行。
- 可将文件或目录中的文本文件的换行符统一转换为指定的系统所用的格式，如Windows（CRLF）、Linux（LF）、macOS(LF)。
- 支持跳过隐藏文件/文件夹或系统文件/文件夹。
- 生成详细的转换报告，包括每个文件转换前后的路径、转换状态、耗时等信息。
## 系统要求
- **操作系统：** Windows,Linux,macOS
- **编译器：** gcc,Visual Studio
## 编译及运行
- 1.在Windows上编译和运行
  
  · 使用Visual Studio创建新的C语言项目
  
  · 将所有文件添加到项目中
  
  · 编译并运行项目
  
- 2.在Linux上编译和运行

```Bash
sudo apt update
sudo apt install build-essential
cd /path/to/line-ending-converter
gcc -o line-ending-converter main.c file_utils.c line_ending_converter.c file_processor.c arg_parser.c -lm
./line-ending-converter <input_path> <output_path> <system>
```
## 使用方法
```Bash
line-ending-converter <input_path> <output_path> <system>
```
- <input_path>: 输入文件或目录的路径。
- <output_path>: 输出文件或目录的路径。
- <system>: 要转换的系统换行符类型，可选值为 Windows, Linux, macOS。
***
# 软件结构图
```Diff
+--------------------------------------------------+
|                     main.c                       |
|  - 主函数 main                                    |
|  - 解析命令行参数，调用处理函数                     |
+--------------------------------------------------+
                      |
                      v
+--------------------------------------------------+
|                   arg_parser.h/c                 |
|  - parse_arguments                               |
|  - 解析命令行参数，获取输入、输出路径和换行符        |
+--------------------------------------------------+
                      |
                      v
+--------------------------------------------------+
|                   file_utils.h/c                 |
|  - is_hidden_or_system_file                      |
|  - is_hidden_or_system_dir                       |
|  - is_directory                                  |
|  - 判断文件或目录类型                              |
+--------------------------------------------------+
                      |
                      v
+--------------------------------------------------+
|           line_ending_converter.h/c              |
|  - convert_line_endings                          |
|  - 转换文件中的换行符                              |
+--------------------------------------------------+
                      |
                      v
+--------------------------------------------------+
|                 file_processor.c                 |
|  - process_file                                  |
|  - process_directory                             |
|  - 处理文件和目录，调用转换函数                     |
+--------------------------------------------------+
```
***
# 软件流程图
![image](https://github.com/StairJumperWei/line-ending-converter/assets/42022174/37497064-4c33-45cb-b312-648908f43438)
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
