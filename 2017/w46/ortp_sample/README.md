分析基础的RTP发送和接收流程，根据src/test/中的例子简化而来。
对例程进行缩减以简化复杂度

用的是 oRTP 1.0.2版本

#### 文件说明：

rtpsemd.c 发送程序 
rtprecv.c 接收程序

两个程序需要组队使用才行。


**编译命令：**
```
gcc -g  rtpsend.c  -o  rtpsend  `pkg-config --cflags --libs  ortp`
gcc -g  rtprecv.c  -o  rtprecv  `pkg-config --cflags --libs  ortp`
```


**设置环境变量：**

```
export LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH
```

**运行命令：**


```
./rtprecv  recv_filename  9000

./rtpsend  160.file  127.0.0.1  9000
```







