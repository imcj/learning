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

PHP Select benchmark
--------------------

```
ab -r -c 100 -n 4000 http://127.0.0.1:8000/
This is ApacheBench, Version 2.3 <$Revision: 1807734 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
...
Finished 4000 requests


Server Software:        TestServer/1.0.0
Server Hostname:        127.0.0.1
Server Port:            8000

Document Path:          /
Document Length:        11 bytes

Concurrency Level:      100
Time taken for tests:   0.413 seconds
Complete requests:      4000
Failed requests:        0
Total transferred:      660000 bytes
HTML transferred:       44000 bytes
Requests per second:    9676.75 [#/sec] (mean)
Time per request:       10.334 [ms] (mean)
Time per request:       0.103 [ms] (mean, across all concurrent requests)
Transfer rate:          1559.24 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.4      0       4
Processing:     1   10   1.3     10      13
Waiting:        1   10   1.3     10      13
Total:          5   10   1.0     10      13

Percentage of the requests served within a certain time (ms)
  50%     10
  66%     10
  75%     11
  80%     11
  90%     11
  95%     12
  98%     13
  99%     13
 100%     13 (longest request)
```
