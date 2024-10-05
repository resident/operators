<?php

declare(strict_types=1);

class Number
{
    public int|float $var = 0;

    public function __construct(int|float $x = 0)
    {
        $this->var = $x;
    }

    /**
     * @throws Exception
     */
    private function getScalarOps(mixed ...$ops): array
    {
        $result = [];

        foreach ($ops as $op) {
            if ($op instanceof Number) {
                $result[] = $op->var;
            } else {
                if (is_scalar($op)) {
                    $result[] = $op;
                } elseif (is_object($op) && property_exists($op, 'var')) {
                    $result[] = $op->var;
                } else {
                    throw new Exception("Unsupported operand type");
                }
            }
        }

        return $result;
    }

    /************************ ARITHMETIC ****************************
     * @throws Exception
     */
    public function __add($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 + $op2);
    }

    /**
     * @throws Exception
     */
    public function __sub($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 - $op2);
    }

    /**
     * @throws Exception
     */
    public function __mul($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 * $op2);
    }

    /**
     * @throws Exception
     */
    public function __pow($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 ** $op2);
    }

    /**
     * @throws Exception
     */
    public function __div($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 / $op2);
    }

    /**
     * @throws Exception
     */
    public function __mod($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 % $op2);
    }

    /**
     * @throws Exception
     */
    public function __sl($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 << $op2);
    }

    /**
     * @throws Exception
     */
    public function __sr($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 >> $op2);
    }

    /************************** STRINGS **************************
     * @throws Exception
     */

    public function __concat($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 + $op2);
    }

    /************************* LOGIC ***************************
     * @throws Exception
     */
    public function __bwOr($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 | $op2);
    }

    /**
     * @throws Exception
     */
    public function __bwAnd($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 & $op2);
    }

    /**
     * @throws Exception
     */
    public function __bwXor($op1, $op2): static
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return new static($op1 ^ $op2);
    }

    public function __bwNot(): int|string
    {
        return ~$this->var;
    }

    public function __boolNot(): bool
    {
        return !$this->var;
    }

    /**
     * @throws Exception
     */
    public function __boolXor($op1, $op2): bool
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return $op1 xor $op2;
    }

    /********************** COMPARISONS *************************/
    public function __isIdentical($op1, $op2): bool
    {
        return $op1 instanceof self && $op2 instanceof self && $op1->var === $op2->var;
    }

    public function __isNotIdentical($op1, $op2): bool
    {
        return !$this->__isIdentical($op1, $op2);
    }

    /**
     * @throws Exception
     */
    public function __isEqual($op1, $op2): bool
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return $op1 == $op2;
    }

    /**
     * @throws Exception
     */
    public function __isNotEqual($op1, $op2): bool
    {
        return !$this->__isEqual($op1, $op2);
    }

    /**
     * @throws Exception
     */
    public function __isSmaller($op1, $op2): bool
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return $op1 < $op2;
    }

    /**
     * @throws Exception
     */
    public function __isSmallerOrEqual($op1, $op2): bool
    {
        [$op1, $op2] = $this->getScalarOps($op1, $op2);

        return $op1 <= $op2;
    }

    /************************* ASSIGNS *************************/
    public function __assign(Number|int|float $value): Number
    {
        if (is_numeric($value)) {
            $this->var = $value;
            return $this;
        }

        return $value;
    }

    /**
     * @throws Exception
     */
    public function __assignOp(mixed $value, int $opcode): static
    {
        $result = match ($opcode) {
            Operators\OP_ADD => $this->__add($this, $value),
            Operators\OP_SUB => $this->__sub($this, $value),
            Operators\OP_MUL => $this->__mul($this, $value),
            Operators\OP_POW => $this->__pow($this, $value),
            Operators\OP_DIV => $this->__div($this, $value),
            Operators\OP_MOD => $this->__mod($this, $value),
            Operators\OP_SL => $this->__sl($this, $value),
            Operators\OP_SR => $this->__sr($this, $value),
            Operators\OP_CONCAT => $this->__concat($this, $value),
            Operators\OP_BW_OR => $this->__bwOr($this, $value),
            Operators\OP_BW_AND => $this->__bwAnd($this, $value),
            Operators\OP_BW_XOR => $this->__bwXor($this, $value),

            default => throw new Exception("Unsupported operation, opcode: $opcode")
        };

        $this->var = $result->var;

        return $this;
    }

    /*********************** INC / DEC *****************************/
    public function __preInc(): static
    {
        ++$this->var;

        return $this;
    }

    public function __preDec(): static
    {
        --$this->var;

        return $this;
    }

    public function __postInc(): static
    {
        $tmp = clone $this;

        ++$this->var;

        return $tmp;
    }

    public function __postDec(): static
    {
        $tmp = clone $this;

        --$this->var;

        return $tmp;
    }

    public function __preIncObj(): int|float
    {
        return $this->var + 1;
    }

    public function __preDecObj(): int|float
    {
        return $this->var - 1;
    }

    public function __postIncObj(): int|float
    {
        return $this->var++;
    }

    public function __postDecObj(): int|float
    {
        return $this->var--;
    }

    /**
     * @throws Exception
     */
    public function __cast(int $type): float|object|int|array|string
    {
        $result = match($type) {
            Operators\IS_LONG => (int) $this->var,
            Operators\IS_DOUBLE => (double) $this->var,
            Operators\IS_STRING => (string) $this->var,
            Operators\IS_ARRAY => (array) $this->var,
            Operators\IS_OBJECT => (object) $this->var,

            default => throw new Exception('Unsupported type'),
        };

        return $result;
    }

    public function __bool(): bool
    {
        return (bool)$this->var;
    }
}
