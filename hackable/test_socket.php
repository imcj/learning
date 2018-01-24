<?php
// fd_set_new();

class PollEvent
{
	public function fired()
	{

	}
}

class Poll
{
	private $fds;
	private $total;

	public function __construct($total = 10240)
	{
		$this->pollfds = pollfd_set_new($total);
		for ($i = 0; $i < $totoal; $i++) {
			pollfd_set($this->fds, $i, -1, 0);
		}
	}

	// public function add()
}

$fd = socket();
bind($fd, "0.0.0.0", 8000);
// listen($fd, 5);
$pollfds = pollfd_set_new(10240);
pollfd_set($pollfds, 0, $fd, POLLOUT);

list($poll_fd, $poll_events, $poll_revents) = pollfd_get($pollfds, 0);
$ready = poll($pollfds, 1, 10000);
var_dump($ready);
assert($fd == $poll_fd);