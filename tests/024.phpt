--TEST--
Operators +=, -=, *=, **=, /=, %=, <<=, >>=, .=, |=, &=, ^= overload
--EXTENSIONS--
operators
--FILE--
<?php
ini_set('operators.overload.assign_op', true);

include 'Number.php';

$n = new Number(10);

echo ($n += 3)->var, "\n";
echo ($n -= 3)->var, "\n";
echo ($n *= 3)->var, "\n";
echo ($n **= 3)->var, "\n";
echo ($n /= 3)->var, "\n";
echo ($n %= 7)->var, "\n";
echo ($n <<= 3)->var, "\n";
echo ($n >>= 3)->var, "\n";
echo ($n .= 3)->var, "\n";
echo ($n |= 0b11)->var, "\n";
echo ($n &= 0b11)->var, "\n";
echo ($n ^= 0b11)->var, "\n";

?>
--EXPECT--
13
10
30
27000
9000
5
40
5
8
11
3
0
