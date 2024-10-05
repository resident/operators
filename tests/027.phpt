--TEST--
Operator post increment overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.post_inc', true);

include 'Number.php';

$n = new Number(10);

echo ($n++)->var, "\n";
echo $n->var;

?>
--EXPECT--
10
11
