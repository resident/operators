--TEST--
Cast operator overload
--EXTENSIONS--
operators
--FILE--
<?php

ini_set('operators.overload.cast', true);

include 'Number.php';

$n = new Number(10);

var_dump((int) $n);
var_dump((float) $n);
var_dump((double) $n);
var_dump((string) $n);
var_dump((array) $n);
var_dump((object) $n);

?>
--EXPECT--
int(10)
float(10)
float(10)
string(2) "10"
array(1) {
  [0]=>
  int(10)
}
object(stdClass)#2 (1) {
  ["scalar"]=>
  int(10)
}