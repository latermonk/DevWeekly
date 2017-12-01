# Linux命令行代理工具：





```
cd ~
git clone https://github.com/rofl0r/proxychains-ng.git
cd proxychains-ng
./configure && make && make install
make install-config
```



vim /usr/local/etc/proxychains.conf

替换：


```
socks4 127.0.0.1 9050
```

为：


```
socks5 127.0.0.1 1080
```




之后命令行使用代理的时候：



```
proxychain4 xxxxxxxxx
```

 即可。



