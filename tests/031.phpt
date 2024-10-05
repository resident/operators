--TEST--
Operator post increment obj prop overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.post_inc_obj', true);

include 'Number.php';

$n = new Number(10);

echo $n->var++, "\n";
echo $n->var;

?>
--EXPECT--
10
11