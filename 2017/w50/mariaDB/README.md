# 安装

```
yum install mariadb mariadb-server

systemctl start mariadb ==> 启动mariadb

systemctl enable mariadb ==> 开机自启动

mysql_secure_installation ==> 设置 root密码等相关 /*密码passwd*/

mysql -uroot -p123456 ==> 测试登录！

```

# 配置远程连接

```
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%'IDENTIFIED BY 'passwd' WITH GRANT OPTION;
```

