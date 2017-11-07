# pkg-config 使用方法

## 0.安装

Linux平台要先安装此工具才行。



## 1.使用方法：

mac下 ：

```Shell
pkg-config --libs --cflags  lua
```

结果：

```
-I/usr/local/opt/lua/include -L/usr/local/opt/lua/lib -llua -lm
```

这个其实就是编译常见的**头文件 库文件**位置的指定。



### 常用命令：

```Shell
pkg-config --list-all    可以列出所有可使用的包
```

```
pkg-config --libs ortp   查看ortp库的情况和配置
```

如果没有要查看 

```shell
echo $PKG_CONFIG_PATH  的结果，如果没有的话，要执行以下命令：
```



```shell
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib64/lib/pkgconfig/   指定.pc文件的路径
export PKG_CONFIG_PATH                                       让配置文件生效
```

或者写成一句话：

```shell
export PKG_CONFIG_PATH=/opt/gtk/lib/pkgconfig:$PKG_CONFIG_PATH  指定.pc文件的路径
```



配置成功之后，务必使用：

```
echo $PKG_CONFIG_PATH 命令查看路径有没有写到配置路径里边
```



### 指定库的路径：

如果使用了库文件的话，在执行的时候还需要设置： LD_LIBRARY_PATH

```shell
export LD_LIBRARY_PATH=/opt/gtk/lib:$LD_LIBRARY_PATH
```



然后使用命令：

```shell
echo $LD_LIBRARY_PATH  查看路径，看是否把动态库的路径加入到库的路径配置中
```





## 2.大坑

编译的时候用 pkg-config 发现始终无法编译通过，总是报错说 xxx库找不到，百思不得姐.

后来网上搜索到 pkg-config 的section 应该用 **<u>倒引号</u>**来包含，如下：



```shell
gcc -g  test.c  -o  test  ̀pkg-config --cflags --libs  ortp`  //	切记， 切记 ！！！ 
```





## 3.进阶

如何自定义 .pc文件 ？



看Demo:



```
Name: opencv
Description:OpenCV pc file
Version: 2.4
Cflags:-I/usr/local/include
Libs:-L/usr/local/lib –lxxx –lxxx
```



记得要把.pc文件的路径写到 **$PKG_CONFIG_PATH** 变量中。





-------

完