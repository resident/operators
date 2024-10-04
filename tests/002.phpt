--TEST--
test1() Basic test
--EXTENSIONS--
operators
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension operators is loaded and working!
NULL
