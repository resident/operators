--TEST--
Operator <= overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.is_smaller_or_equal', true);

include 'Number.php';

$n1 = new Number(1);
$n2 = new Number(1);
$n3 = new class {
    public $var = 2;
};
$n4 = new class {};

var_dump($n1 <= $n1);
var_dump($n1 <= $n2);
var_dump($n1 <= $n3);

try {
    var_dump($n1 <= $n4);
} catch (Throwable $e) {
    echo $e->getMessage();
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
Unsupported operand type
