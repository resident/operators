--TEST--
Operator pre decrement overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.pre_dec', true);

include 'Number.php';

$n = new Number(10);

echo (--$n)->var;

?>
--EXPECT--
9
