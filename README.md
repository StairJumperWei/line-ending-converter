## Windows、Linux、MacOS三个系统中，文本的换行符格式不同。编写一个换行符格式转换工具，实现三个系统间的换行符格式的转换。

**Usage:** .\line_ending_converter.exe <input_file> <output_flie> < system >

**system option:** Windows, Linux, macOS

***
# 软件结构图
![image](https://github.com/StairJumperWei/line-ending-converter/assets/42022174/466887e1-733b-44e0-b3d2-8f954118f2cb)
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
