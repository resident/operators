--TEST--
Operator ! overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.bool_not', true);

include 'Number.php';

$n1 = new Number(0);
$n2 = new Number(10);

var_dump(!$n1);
var_dump(!$n2);

?>
--EXPECT--
bool(true)
bool(false)
