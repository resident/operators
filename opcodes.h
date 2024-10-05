#ifndef OPCODES_H
#define OPCODES_H

#include "php.h"

zend_bool *opcode_handlers_status[ZEND_VM_LAST_OPCODE + 1];

zend_uchar opcode_handlers[] = {
    ZEND_ADD,
    ZEND_SUB,
    ZEND_MUL,
    ZEND_DIV,
    ZEND_MOD,
    ZEND_SL,
    ZEND_SR,

    ZEND_CONCAT,

    ZEND_BW_OR,
    ZEND_BW_AND,
    ZEND_BW_XOR,
    ZEND_POW,
    ZEND_BW_NOT,
    ZEND_BOOL_NOT,
    ZEND_BOOL_XOR,

    ZEND_IS_IDENTICAL,
    ZEND_IS_NOT_IDENTICAL,
    ZEND_IS_EQUAL,
    ZEND_IS_NOT_EQUAL,
    ZEND_IS_SMALLER,
    ZEND_IS_SMALLER_OR_EQUAL,

    ZEND_ASSIGN,
    ZEND_ASSIGN_OP,

    ZEND_PRE_INC,
    ZEND_PRE_DEC,
    ZEND_POST_INC,
    ZEND_POST_DEC,
    ZEND_PRE_INC_OBJ,
    ZEND_PRE_DEC_OBJ,
    ZEND_POST_INC_OBJ,
    ZEND_POST_DEC_OBJ,

    ZEND_CAST,
    ZEND_BOOL,
};

#endif //OPCODES_H
