--TEST--
Operator (bool) overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.bool', true);

include 'Number.php';

var_dump((bool) new Number(10));
var_dump((bool) new Number(0));

?>
--EXPECT--
bool(true)
bool(false)