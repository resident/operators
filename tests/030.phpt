--TEST--
Operator pre decrement obj prop overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.pre_dec_obj', true);

include 'Number.php';

$n = new Number(10);

echo --$n->var;

?>
--EXPECT--
9