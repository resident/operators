--TEST--
Operator / overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.div', true);

include 'Number.php';

echo (new Number(10) / 2)->var;

?>
--EXPECT--
5
