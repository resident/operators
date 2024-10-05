--TEST--
Operator . overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.concat', true);

include 'Number.php';

echo (new Number(10) . 3)->var;

?>
--EXPECT--
13
