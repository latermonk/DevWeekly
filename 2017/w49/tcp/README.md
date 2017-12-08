#Linux常见的网络命令

## 1检查TCP连接
### 1.1 检测web服务器的链接数量及状态

```
netstat -ant|awk '{print $5 "\t" $6}'|grep "::ffff:"|sed -e 's/::ffff://' -e 's/:[0-9]*//' |sort|uniq -c| sort -rn|head -10
```
### 1.2 检测所有的tcp连接数量及状态

```
netstat -ant|awk '{print $5 "\t" $6}' |grep "[1-9][0-9]*\."|sed -e 's/::ffff://' -e 's/:[0-9]*//'|sort|uniq -c|sort -nr|head -10
```


## 2
### 3

