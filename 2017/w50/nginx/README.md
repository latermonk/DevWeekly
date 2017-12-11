# Nginx

## 准备工作

```
yum install -y pcre pcre-devel
yum install -y zlib zlib-devel
yum install -y openssl openssl-devel
```


## 编译



```
./configure
```



```
make
```

## 安装

```
make install
```

## 管理命令
### 查找安装路径

```
whereis nginx
```
### 启动停止

```
cd /usr/local/nginx/sbin/
./nginx 
./nginx -s stop
./nginx -s quit
./nginx -s reload
./nginx -s quit:此方式停止步骤是待nginx进程处理任务完毕进行停止。
./nginx -s stop:此方式相当于先查出nginx进程id再使用kill命令强制杀掉进程。

查询nginx进程：

ps aux|grep nginx
```


### 重启

```
1.先停止再启动（推荐）：

对 nginx 进行重启相当于先停止再启动，即先执行停止命令再执行启动命令。如下：

./nginx -s quit
./nginx


2.重新加载配置文件：

当 ngin x的配置文件 nginx.conf 修改后，要想让配置生效需要重启 nginx，使用-s reload不用先停止 ngin x再启动 nginx 即可将配置信息在 nginx 中生效，如下：
./nginx -s reload
```


### 开机自启动


即在rc.local增加启动代码就可以了。

```
vim /etc/rc.local
增加一行 /usr/local/nginx/sbin/nginx

设置执行权限：
chmod 755 rc.local
```


## 实践方法
* 配置php
* 做代理
* 做反向代理
* 负载均衡
* etc

