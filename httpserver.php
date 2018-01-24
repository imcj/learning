<?php
set_time_limit(0);

$address = '127.0.0.1';
$port = 8000;

$sock = socket_create(AF_INET, SOCK_STREAM, 0);
socket_set_option($sock, SOL_SOCKET, SO_REUSEPORT, 1);
socket_set_option($sock, SOL_TCP, TCP_NODELAY, 1);
socket_set_option($sock, SOL_SOCKET, SO_REUSEADDR, 1);
socket_bind($sock, $address, $port) or die('Could not bind to address');
socket_listen($sock, 10000000);
socket_set_nonblock($sock);
echo (int)$sock . "\n";

class Request
{
    public $socket;
    public $sendOffset = 0;
    public $rtime = 0;
    public $wtime = 0;
}


$fds = [
];

$r = new Request();
$r->socket = $sock;

$fds[(int)$sock] = $r;

$requests = [];

$sds = [

];


const BUFFER_SIZE = 512;
const OUT = 'HTTP/1.1 200 OK
Server: TestServer/1.0.0 (PHPServ)
Date: Fri, 12 Jan 2018 17:40:12 GMT
Content-Length: 11
Content-Type: text/html
Connection: Keep-Alive

hello world';

function fib($n) {
    if ($n < 2)
        return $n;

    return fib($n - 1) + fib($n - 2);
}

// $fds = [$sock]

function callback($c)
{

}

function microtime_float()
{
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}
function handle($client)
{
    global $fds;
    $input = '';

    $data = '';
    $bufferSize = 512;
    for (;;) {
        $r = [$client];
        $w = [];
        $e = [];
        $r2 = socket_select($r, $w, $e, 1);

        $buffer = '';
        $error = socket_recv($client, $buffer, $bufferSize, MSG_DONTWAIT);
        // $data .= $buffer;
        $rlen = strlen($buffer);


        if ($rlen < $bufferSize) {
            // echo "buffer $rlen < 10\n";
            
            break;
        }
        if ($buffer == null) {
            echo "buffer is null \n";
            break;
        }
    }
    // echo $data;
    // echo "request end\n";


    $output = 'HTTP/1.1 200 OK
Server: TestServer/1.0.0 (PHPServ)
Content-Length: 10
Content-Type: text/html

hello world';
    socket_write($client, $output);

    socket_close($client);
}

function handleBuffer($client)
{
    global $requests;
    global $fds;
    global $sds;

    $r2 = $fds[(int)$client];

    $t1 = microtime_float();

    $cid = (int)$client;
    $buffer = '';
    $error = socket_recv($client, $buffer, BUFFER_SIZE, MSG_DONTWAIT);
    $rlen = strlen($buffer);

    $r2->rtime += microtime_float() - $t1;

    if (!isset($requests[$cid])) {
        $requests[$cid] = '';
    }

    $requests[$cid] .= $buffer;

    if ($rlen < BUFFER_SIZE || $buffer == null) {
        // echo "buffer $rlen < 10\n";
        // socket_write($client, OUT);
        // socket_send()
        if ($r2->rtime > 0.01)
            echo "timeout {$r2->rtime}" . PHP_EOL;
        
        // $x = "";
        // $x2 = '';
        // for ($i = 0; $i < 100; $i++) {
        //     // $x .= str_repeat(" ", 100);
        //     // $x2[] = str_repeat(" ", 100);;
        //     for ($j = 0; $j < 100; $j++) {
        //         $x2 .= ' ';
        //     }
        // }
        // echo strlen($x);
        unset($fds[$cid]);
        $s = new Request();
        $s->socket = $client;
        $s->sendOffset = 0;
        $sds[$cid] = $s;
        
        // break;
    }
    // if () {
    //     echo "buffer is null \n";
    //     // break;
    // }
}

function handleSend($client)
{
    global $sds;
    $cid = (int)$client;
    $r = $sds[$cid];
    $t1 = microtime_float();
    
    $sbuf = substr(OUT, $r->sendOffset);
    $ret = socket_send($r->socket, $sbuf, BUFFER_SIZE, 0);

    $r->wtime += microtime_float() - $t1;

    if ($ret < BUFFER_SIZE) {
        if ($r->wtime > 0.01)
            echo "timeout {$r->wtime}" . PHP_EOL;

        unset($sds[$cid]);
        
        @socket_shutdown($r->socket, 2);
        socket_close($r->socket);
    }
}

while(1)
{
    $r = array_map(function($r) {
        return $r->socket;
    }, $fds);

    // echo count($r).PHP_EOL;

    $w = array_map(function($r) {
        return $r->socket;
    }, $sds);
    // var_dump($w);
    // var_dump($sds);
    $e = [];
    $t1 = microtime_float();
    $r2 = socket_select($r, $w, $e, 1);
    $t2 = microtime_float() - $t1;
    // echo count($r2) . " " . $t2 . PHP_EOL;

    if (0 == $r2)
        continue;

    while (true) {
        if (count($r) == 0)
            break;
        $s = array_pop($r);

        if ($s == $sock) {
            $t1 = microtime_float();
            $client = socket_accept($sock);
            socket_set_nonblock($client);
            $t2 = microtime_float() - $t1;
            // echo $t2 . PHP_EOL;
            if ($t2 > 0.1) {
                echo "time out\n";
            }

            $re = new Request();
            $re->socket = $client;

            $fds[(int)$client] = $re;
        } else {
            handleBuffer($s);
            
        }
    }

    while ($w2 = array_pop($w)) {
        handleSend($w2);
    }
    
}

socket_close($sock);
?>