--TEST--
Operator post decrement overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.post_dec', true);

include 'Number.php';

$n = new Number(10);

echo ($n--)->var, "\n";
echo $n->var;

?>
--EXPECT--
10
9
