--TEST--
Operator pre increment overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.pre_inc', true);

include 'Number.php';

$n = new Number(10);

echo (++$n)->var;

?>
--EXPECT--
11
