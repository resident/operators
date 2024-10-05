--TEST--
Operator ~ overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.bw_not', true);

include 'Number.php';

$n = new Number(PHP_INT_MAX << 1);

echo decbin(~$n);

?>
--EXPECT--
1
