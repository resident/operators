--TEST--
Operator = overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.assign', true);

include 'Number.php';

$n = new Number();

$n = 3;

print_r($n);

$n = new Number(10);

print_r($n);

try {
    $n = "wrong type";
} catch (TypeError $e) {
    echo "Wrong type\n";
}

?>
--EXPECT--
Number Object
(
    [var] => 3
)
Number Object
(
    [var] => 10
)
Wrong type