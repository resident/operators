--TEST--
Operator post decrement obj prop overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.post_dec_obj', true);

include 'Number.php';

$n = new Number(10);

echo $n->var--, "\n";
echo $n->var;

?>
--EXPECT--
10
9