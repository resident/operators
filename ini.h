#ifndef INI_H
#define INI_H

#include "globals.h"
#include "php_ini.h"

PHP_INI_BEGIN()
    STD_PHP_INI_BOOLEAN("operators.overload.add", "0", PHP_INI_ALL, OnUpdateBool, overload_add, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.sub", "0", PHP_INI_ALL, OnUpdateBool, overload_sub, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.mul", "0", PHP_INI_ALL, OnUpdateBool, overload_mul, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.div", "0", PHP_INI_ALL, OnUpdateBool, overload_div, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.mod", "0", PHP_INI_ALL, OnUpdateBool, overload_mod, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.sl", "0", PHP_INI_ALL, OnUpdateBool, overload_sl, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.sr", "0", PHP_INI_ALL, OnUpdateBool, overload_sr, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.concat", "0", PHP_INI_ALL, OnUpdateBool, overload_concat, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.bw_or", "0", PHP_INI_ALL, OnUpdateBool, overload_bw_or, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bw_and", "0", PHP_INI_ALL, OnUpdateBool, overload_bw_and, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bw_xor", "0", PHP_INI_ALL, OnUpdateBool, overload_bw_xor, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.pow", "0", PHP_INI_ALL, OnUpdateBool, overload_pow, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bw_not", "0", PHP_INI_ALL, OnUpdateBool, overload_bw_not, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bool_not", "0", PHP_INI_ALL, OnUpdateBool, overload_bool_not, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bool_xor", "0", PHP_INI_ALL, OnUpdateBool, overload_bool_xor, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.is_identical", "0", PHP_INI_ALL, OnUpdateBool, overload_is_identical, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.is_not_identical", "0", PHP_INI_ALL, OnUpdateBool, overload_is_not_identical, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.is_equal", "0", PHP_INI_ALL, OnUpdateBool, overload_is_equal, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.is_not_equal", "0", PHP_INI_ALL, OnUpdateBool, overload_is_not_equal, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.is_smaller", "0", PHP_INI_ALL, OnUpdateBool, overload_is_smaller, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.is_smaller_or_equal", "0", PHP_INI_ALL, OnUpdateBool, overload_is_smaller_or_equal, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.assign", "0", PHP_INI_ALL, OnUpdateBool, overload_assign, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.assign_op", "0", PHP_INI_ALL, OnUpdateBool, overload_assign_op, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.pre_inc", "0", PHP_INI_ALL, OnUpdateBool, overload_pre_inc, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.pre_dec", "0", PHP_INI_ALL, OnUpdateBool, overload_pre_dec, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.post_inc", "0", PHP_INI_ALL, OnUpdateBool, overload_post_inc, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.post_dec", "0", PHP_INI_ALL, OnUpdateBool, overload_post_dec, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.pre_inc_obj", "0", PHP_INI_ALL, OnUpdateBool, overload_pre_inc_obj, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.pre_dec_obj", "0", PHP_INI_ALL, OnUpdateBool, overload_pre_dec_obj, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.post_inc_obj", "0", PHP_INI_ALL, OnUpdateBool, overload_post_inc_obj, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.post_dec_obj", "0", PHP_INI_ALL, OnUpdateBool, overload_post_dec_obj, zend_operators_globals, operators_globals)

    STD_PHP_INI_BOOLEAN("operators.overload.cast", "0", PHP_INI_ALL, OnUpdateBool, overload_cast, zend_operators_globals, operators_globals)
    STD_PHP_INI_BOOLEAN("operators.overload.bool", "0", PHP_INI_ALL, OnUpdateBool, overload_bool, zend_operators_globals, operators_globals)
PHP_INI_END()

#endif //INI_H
