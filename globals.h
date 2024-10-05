#ifndef GLOBALS_H
#define GLOBALS_H

#include "php.h"

ZEND_BEGIN_MODULE_GLOBALS(operators)
    zend_bool overload_add;
    zend_bool overload_sub;
    zend_bool overload_mul;
    zend_bool overload_div;
    zend_bool overload_mod;
    zend_bool overload_sl;
    zend_bool overload_sr;

    zend_bool overload_concat;

    zend_bool overload_bw_or;
    zend_bool overload_bw_and;
    zend_bool overload_bw_xor;
    zend_bool overload_pow;
    zend_bool overload_bw_not;
    zend_bool overload_bool_not;
    zend_bool overload_bool_xor;

    zend_bool overload_is_identical;
    zend_bool overload_is_not_identical;
    zend_bool overload_is_equal;
    zend_bool overload_is_not_equal;
    zend_bool overload_is_smaller;
    zend_bool overload_is_smaller_or_equal;

    zend_bool overload_assign;
    zend_bool overload_assign_op;

    zend_bool overload_pre_inc;
    zend_bool overload_pre_dec;
    zend_bool overload_post_inc;
    zend_bool overload_post_dec;
    zend_bool overload_pre_inc_static_prop;
    zend_bool overload_pre_dec_static_prop;
    zend_bool overload_post_inc_static_prop;
    zend_bool overload_post_dec_static_prop;
    zend_bool overload_pre_inc_obj;
    zend_bool overload_pre_dec_obj;
    zend_bool overload_post_inc_obj;
    zend_bool overload_post_dec_obj;

    zend_bool overload_cast;
    zend_bool overload_bool;

ZEND_END_MODULE_GLOBALS(operators)

ZEND_DECLARE_MODULE_GLOBALS(operators)

#endif //GLOBALS_H
