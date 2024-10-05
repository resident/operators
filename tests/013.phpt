--TEST--
Operator ^ overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.bw_xor', true);

include 'Number.php';

echo decbin((new Number(0b1010) ^ 0b11)->var);

?>
--EXPECT--
1001
