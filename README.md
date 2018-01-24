Learning
========

httpserver.php
--------------

用纯PHP写的HTTP Server演示，每秒吞吐量8000+ QPS。

hackable
--------

PHP 扩展增加了select poll pollfd的操作，目的是以最底层的Unix socket编程完成HTTP Server的任务。

TODO
----

- [ ] 增加select函数
- [ ] 增加fcntl函数
- [ ] 增加event loop
- [ ] 增加epoll支持
- [ ] 增加event base http 协议分析
