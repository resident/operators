--TEST--
Operator === overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.is_identical', true);

include 'Number.php';

$n1 = new Number(10);
$n2 = new Number(10);
$n3 = new class {
    public $var = 10;
};

var_dump($n1 === $n1);
var_dump($n1 === $n2);
var_dump($n1 === $n3);

?>
--EXPECT--
bool(true)
bool(true)
bool(false)
