--TEST--
Operator pre increment obj prop overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.pre_inc_obj', true);

include 'Number.php';

$n = new Number(10);

echo ++$n->var;

?>
--EXPECT--
11