--TEST--
Operator xor overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.bool_xor', true);

include 'Number.php';

var_dump(new Number(10) xor 1);
var_dump(new Number(0) xor 1);

?>
--EXPECT--
bool(false)
bool(true)