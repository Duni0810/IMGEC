
# 编译方法

 - 电脑必须拥有keil C51 编译环境（keil3，keil4或者keil5都可），因为使用命令行编译要用到C51 的链接器；
 - 修改链接环境，打开 build.bat ，修改 path 变量中的地址：

``` c
path=C:\Keil_v5\C51\BIN;.\..\Tools;.\..\Tools\NMake;
```
将  **C:\Keil_v5\C51\BIN** 修改为 当前你的keil编译环境；

 - 编译工程，打开 cmd 输入 make.bat，然后回车即可；

 - 清除编译产生的临时文件，双击 clear.bat；



# 部分文件介绍

## IMGEC.lin
编译的链接文件，如果需修改或者添加文件，就必须在该文件中添加相应的OBJ;



## IMGEC.mak
编译的 代码的 makefile 文件，如果需修改或者添加文件，就必须在该文件中添加相应的文件;


