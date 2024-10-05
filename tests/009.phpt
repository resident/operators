--TEST--
Operator >> overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.sr', true);

include 'Number.php';

echo decbin((new Number(0b1010) >> 1)->var);

?>
--EXPECT--
101
