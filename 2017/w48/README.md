

# ssh usage:


```
#!/usr/bin/expect
spawn /usr/bin/ssh -nNfT  -D 1080 root@1.2.3.4
expect "*password:"
send "this-is-a-ssh-passwd-of-ssh-server\r"
expect "*]#"
```


-------



# Linux terminal proxy tool：





```
cd ~
git clone https://github.com/rofl0r/proxychains-ng.git
cd proxychains-ng
./configure && make && make install
make install-config
```


**vim /usr/local/etc/proxychains.conf**

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



-------


