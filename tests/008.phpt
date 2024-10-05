--TEST--
Operator << overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.sl', true);

include 'Number.php';

echo decbin((new Number(0b1010) << 1)->var);

?>
--EXPECT--
10100
