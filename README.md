# PHP Operator Overloading

This extension allows you to overload operators in PHP.

## Installation

    git clone https://github.com/resident/operators.git
    phpize
    ./configure
    make
    make install
    make test
    
Add extension to php.ini

    extension=operators.so

## Configuration

By default, all overloads are disabled, to enable the overloads you need set the value to `1` for the configuration option.

After that, you need to implement methods with operator overloading logic in your class.

### php.ini options

| Option                                 |                        Operator                         |           Class method           | Default value |
|:---------------------------------------|:-------------------------------------------------------:|:--------------------------------:|:-------------:|
| operators.overload.add                 |                           `+`                           |       `__add($op1, $op2)`        |       0       |
| operators.overload.sub                 |                           `-`                           |       `__sub($op1, $op2)`        |       0       |
| operators.overload.mul                 |                    `*, +$var, -$var`                    |       `__mul($op1, $op2)`        |       0       |
| operators.overload.pow                 |                          `**`                           |       `__pow($op1, $op2)`        |       0       |
| operators.overload.div                 |                           `/`                           |       `__div($op1, $op2)`        |       0       |
| operators.overload.mod                 |                           `%`                           |       `__mod($op1, $op2)`        |       0       |
| operators.overload.sl                  |                          `<<`                           |        `__sl($op1, $op2)`        |       0       |
| operators.overload.sr                  |                          `>>`                           |        `__sr($op1, $op2)`        |       0       |
| operators.overload.concat              |                           `.`                           |      `__concat($op1, $op2)`      |       0       |
| operators.overload.bw_or               |                          `\|`                           |       `__bwOr($op1, $op2)`       |       0       |
| operators.overload.bw_and              |                           `&`                           |      `__bwAnd($op1, $op2)`       |       0       |
| operators.overload.bw_xor              |                           `^`                           |      `__bwXor($op1, $op2)`       |       0       |
| operators.overload.bw_not              |                           `~`                           |           `__bwNot()`            |       0       |
| operators.overload.bool_not            |                           `!`                           |          `__boolNot()`           |       0       |
| operators.overload.bool_xor            |                          `xor`                          |     `__boolXor($op1, $op2)`      |       0       |
| operators.overload.is_identical        |                          `===`                          |   `__isIdentical($op1, $op2)`    |       0       |
| operators.overload.is_not_identical    |                          `!==`                          |  `__isNotIdentical($op1, $op2)`  |       0       |
| operators.overload.is_equal            |                          `==`                           |     `__isEqual($op1, $op2)`      |       0       |
| operators.overload.is_not_equal        |                          `!=`                           |    `__isNotEqual($op1, $op2)`    |       0       |
| operators.overload.is_smaller          |                           `<`                           |    `__isSmaller($op1, $op2)`     |       0       |
| operators.overload.is_smaller_or_equal |                          `<=`                           | `__isSmallerOrEqual($op1, $op2)` |       0       |
| operators.overload.assign              |                           `=`                           |        `__assign($value)`        |       0       |
| operators.overload.assign_op           |  `+=, -=, *=, **=, /=, %=, <<=, >>=, .=, \|=, &=, ^=`   | `__assignOp($value, int $opcode` |       0       |
| operators.overload.pre_inc             |                        `++$var`                         |           `__preInc()`           |       0       |
| operators.overload.pre_dec             |                        `--$var`                         |           `__preDec()`           |       0       |
| operators.overload.post_inc            |                        `$var++`                         |          `__postInc()`           |       0       |
| operators.overload.post_dec            |                        `$var--`                         |          `__postDec()`           |       0       |
| operators.overload.pre_inc_obj         |                      `++$obj->var`                      |         `__preIncObj()`          |       0       |
| operators.overload.pre_dec_obj         |                      `--$obj->var`                      |         `__preDecObj()`          |       0       |
| operators.overload.post_inc_obj        |                      `$obj->var++`                      |         `__postIncObj()`         |       0       |
| operators.overload.post_dec_obj        |                      `$obj->var--`                      |         `__postDecObj()`         |       0       |
| operators.overload.cast                | `(int), (double), (float), (string), (array), (object)` |       `__cast(int $type)`        |       0       |
| operators.overload.bool                |                        `(bool)`                         |            `__bool()`            |       0       |

## Constants

### Opcodes

| Constant                           | Value |
|:-----------------------------------|:-----:|
| `Operators\OP_ADD`                 |   1   |
| `Operators\OP_SUB`                 |   2   |
| `Operators\OP_MUL`                 |   3   |
| `Operators\OP_DIV`                 |   4   |
| `Operators\OP_MOD`                 |   5   |
| `Operators\OP_SL`                  |   6   |
| `Operators\OP_SR`                  |   7   |
| `Operators\OP_CONCAT`              |   8   |
| `Operators\OP_BW_OR`               |   9   |
| `Operators\OP_BW_AND`              |  10   |
| `Operators\OP_BW_XOR`              |  11   |
| `Operators\OP_POW`                 |  12   |
| `Operators\OP_BW_NOT`              |  13   |
| `Operators\OP_BOOL_NOT`            |  14   |
| `Operators\OP_BOOL_XOR`            |  15   |
| `Operators\OP_IS_IDENTICAL`        |  16   |
| `Operators\OP_IS_NOT_IDENTICAL`    |  17   |
| `Operators\OP_IS_EQUAL`            |  18   |
| `Operators\OP_IS_NOT_EQUAL`        |  19   |
| `Operators\OP_IS_SMALLER`          |  20   |
| `Operators\OP_IS_SMALLER_OR_EQUAL` |  21   |
| `Operators\OP_ASSIGN`              |  22   |
| `Operators\OP_ASSIGN_OP`           |  26   |
| `Operators\OP_PRE_INC`             |  34   |
| `Operators\OP_PRE_DEC`             |  35   |
| `Operators\OP_POST_INC`            |  36   |
| `Operators\OP_POST_DEC`            |  37   |
| `Operators\OP_CAST`                |  51   |
| `Operators\OP_BOOL`                |  52   |
| `Operators\OP_PRE_INC_OBJ`         |  132  |
| `Operators\OP_PRE_DEC_OBJ`         |  133  |
| `Operators\OP_POST_INC_OBJ`        |  134  |
| `Operators\OP_POST_DEC_OBJ`        |  135  |

### Types

| Constant                    | Value |
|:----------------------------|:-----:|
| `Operators\IS_UNDEF`        |   0   |
| `Operators\IS_NULL`         |   1   |
| `Operators\IS_FALSE`        |   2   |
| `Operators\IS_TRUE`         |   3   |
| `Operators\IS_LONG`         |   4   |
| `Operators\IS_DOUBLE`       |   5   |
| `Operators\IS_STRING`       |   6   |
| `Operators\IS_ARRAY`        |   7   |
| `Operators\IS_OBJECT`       |   8   |
| `Operators\IS_RESOURCE`     |   9   |
| `Operators\IS_REFERENCE`    |  10   |
| `Operators\IS_CONSTANT_AST` |  11   |


## Example

See example [Number](https://github.com/resident/operators/blob/main/tests/Number.php) class with overloaded operators.