/* operators extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_operators.h"
#include "operators_arginfo.h"
#include "opcodes.h"
#include "ini.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif


static void convert_opcode_name(const char *input, zend_uchar *output) {
    zend_uchar *ptr = output;

    *ptr++ = '_';
    *ptr++ = '_';

    const char *src = input + 5;

    while (*src) {
        if (*src == '_') {
            src++;
            continue;
        }

        *ptr++ = tolower(*src);

        src++;
    }

    *ptr = '\0';
}

static short set_handler_params(const zend_op *opline, zval *op1, zval *op2, zval* params) {
    short params_count = 0;

    switch (opline->opcode) {
        case ZEND_ADD:
        case ZEND_SUB:
        case ZEND_MUL:
        case ZEND_POW:
        case ZEND_DIV:
        case ZEND_MOD:
        case ZEND_SL:
        case ZEND_SR:
        case ZEND_CONCAT:
        case ZEND_BW_OR:
        case ZEND_BW_AND:
        case ZEND_BW_XOR:
        case ZEND_BOOL_XOR:
        case ZEND_IS_IDENTICAL:
        case ZEND_IS_NOT_IDENTICAL:
        case ZEND_IS_EQUAL:
        case ZEND_IS_NOT_EQUAL:
        case ZEND_IS_SMALLER:
        case ZEND_IS_SMALLER_OR_EQUAL:
        {
            params_count = 2;
            ZVAL_COPY(&params[0], op1);
            ZVAL_COPY(&params[1], op2);
            break;
        }

        case ZEND_BW_NOT:
        case ZEND_BOOL_NOT:
        case ZEND_PRE_INC:
        case ZEND_PRE_DEC:
        case ZEND_POST_INC:
        case ZEND_POST_DEC:
        case ZEND_PRE_INC_OBJ:
        case ZEND_PRE_DEC_OBJ:
        case ZEND_POST_INC_OBJ:
        case ZEND_POST_DEC_OBJ:
        case ZEND_BOOL:
        {
            params_count = 0;
            break;
        }

        case ZEND_ASSIGN:
        {
            params_count = 1;
            ZVAL_COPY(&params[0], op2);
            break;
        }

        case ZEND_ASSIGN_OP:
        {
            params_count = 2;
            ZVAL_COPY(&params[0], op2);
            ZVAL_LONG(&params[1], opline->extended_value);
            break;
        }

        case ZEND_CAST:
        {
            params_count = 1;
            ZVAL_LONG(&params[0], opline->extended_value);
            break;
        }

        default: params_count = 0;
    }

    return params_count;
}

static int op_handler(zend_execute_data *execute_data) {
    const zend_op *opline = EX(opline);

    if (*opcode_handlers_status[opline->opcode] == false) {
        return ZEND_USER_OPCODE_DISPATCH;
    }

    zval *op1, *op2 = NULL;

    if (opline->op1_type == IS_UNUSED) {
        op1 = EX_VAR(opline->result.var);
    } else {
        op1 = zend_get_zval_ptr(opline, opline->op1_type, &opline->op1, execute_data);
    }
    op2 = zend_get_zval_ptr(opline, opline->op2_type, &opline->op2, execute_data);


    zval *op_obj;

    if (Z_TYPE_P(op1) == IS_OBJECT) {
        op_obj = op1;
    } else if (op2 && Z_TYPE_P(op2) == IS_OBJECT) {
        op_obj = op2;
    } else {
        return ZEND_USER_OPCODE_DISPATCH;
    }

    zval *result = NULL;
    if (opline->result_type == IS_UNUSED) {
        result = EX_VAR(opline->op1.var);
    } else if (opline->result_type == IS_VAR || opline->result_type == IS_TMP_VAR) {
        result = EX_VAR(opline->result.var);
    }


    const char* opcode_name = zend_get_opcode_name(opline->opcode);

    char handler_function_name[strlen(opcode_name)];

    convert_opcode_name(opcode_name, handler_function_name);

    const HashTable *function_table = &Z_OBJCE_P(op_obj)->function_table;

    if (zend_hash_str_exists(function_table, handler_function_name, strlen(handler_function_name))) {

        const zval *handler_function = zend_hash_str_find(function_table, handler_function_name, strlen(handler_function_name));

        if (Z_TYPE_P(handler_function) == IS_PTR) {

            const zend_function *func = Z_PTR_P(handler_function);

            if (func->type == ZEND_USER_FUNCTION) {

                zval method_name;

                ZVAL_STR(&method_name, func->internal_function.function_name);

                zval params[2] = {};

                short params_count = set_handler_params(opline, op1, op2, params);

                call_user_function(NULL, op_obj, &method_name, result, params_count, params);

                EX(opline)++;

                return ZEND_USER_OPCODE_CONTINUE;
            }
        }
    }

    return ZEND_USER_OPCODE_DISPATCH;
}

static void overload_operators() {
	for (size_t i = 0; i < sizeof(opcode_handlers); i++) {
		zend_set_user_opcode_handler(opcode_handlers[i], op_handler);
	}
}

static void init_opcode_handlers_status() {
    opcode_handlers_status[ZEND_ADD] = &operators_globals.overload_add;
    opcode_handlers_status[ZEND_SUB] = &operators_globals.overload_sub;
    opcode_handlers_status[ZEND_MUL] = &operators_globals.overload_mul;
    opcode_handlers_status[ZEND_DIV] = &operators_globals.overload_div;
    opcode_handlers_status[ZEND_MOD] = &operators_globals.overload_mod;
    opcode_handlers_status[ZEND_SL] = &operators_globals.overload_sl;
    opcode_handlers_status[ZEND_SR] = &operators_globals.overload_sr;
    opcode_handlers_status[ZEND_CONCAT] = &operators_globals.overload_concat;
    opcode_handlers_status[ZEND_BW_OR] = &operators_globals.overload_bw_or;
    opcode_handlers_status[ZEND_BW_AND] = &operators_globals.overload_bw_and;
    opcode_handlers_status[ZEND_BW_XOR] = &operators_globals.overload_bw_xor;
    opcode_handlers_status[ZEND_POW] = &operators_globals.overload_pow;
    opcode_handlers_status[ZEND_BW_NOT] = &operators_globals.overload_bw_not;
    opcode_handlers_status[ZEND_BOOL_NOT] = &operators_globals.overload_bool_not;
    opcode_handlers_status[ZEND_BOOL_XOR] = &operators_globals.overload_bool_xor;
    opcode_handlers_status[ZEND_IS_IDENTICAL] = &operators_globals.overload_is_identical;
    opcode_handlers_status[ZEND_IS_NOT_IDENTICAL] = &operators_globals.overload_is_not_identical;
    opcode_handlers_status[ZEND_IS_EQUAL] = &operators_globals.overload_is_equal;
    opcode_handlers_status[ZEND_IS_NOT_EQUAL] = &operators_globals.overload_is_not_equal;
    opcode_handlers_status[ZEND_IS_SMALLER] = &operators_globals.overload_is_smaller;
    opcode_handlers_status[ZEND_IS_SMALLER_OR_EQUAL] = &operators_globals.overload_is_smaller_or_equal;
    opcode_handlers_status[ZEND_ASSIGN] = &operators_globals.overload_assign;
    opcode_handlers_status[ZEND_ASSIGN_OP] = &operators_globals.overload_assign_op;
    opcode_handlers_status[ZEND_PRE_INC] = &operators_globals.overload_pre_inc;
    opcode_handlers_status[ZEND_PRE_DEC] = &operators_globals.overload_pre_dec;
    opcode_handlers_status[ZEND_POST_INC] = &operators_globals.overload_post_inc;
    opcode_handlers_status[ZEND_POST_DEC] = &operators_globals.overload_post_dec;
    opcode_handlers_status[ZEND_PRE_INC_OBJ] = &operators_globals.overload_pre_inc_obj;
    opcode_handlers_status[ZEND_PRE_DEC_OBJ] = &operators_globals.overload_pre_dec_obj;
    opcode_handlers_status[ZEND_POST_INC_OBJ] = &operators_globals.overload_post_inc_obj;
    opcode_handlers_status[ZEND_POST_DEC_OBJ] = &operators_globals.overload_post_dec_obj;
    opcode_handlers_status[ZEND_CAST] = &operators_globals.overload_cast;
    opcode_handlers_status[ZEND_BOOL] = &operators_globals.overload_bool;
}

static void register_constants(INIT_FUNC_ARGS) {
    // OPCODES
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_ADD", ZEND_ADD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_SUB", ZEND_SUB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_MUL", ZEND_MUL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_DIV", ZEND_DIV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_MOD", ZEND_MOD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_SL", ZEND_SL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_SR", ZEND_SR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_CONCAT", ZEND_CONCAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BW_OR", ZEND_BW_OR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BW_AND", ZEND_BW_AND, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BW_XOR", ZEND_BW_XOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_POW", ZEND_POW, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BW_NOT", ZEND_BW_NOT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BOOL_NOT", ZEND_BOOL_NOT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BOOL_XOR", ZEND_BOOL_XOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_IDENTICAL", ZEND_IS_IDENTICAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_NOT_IDENTICAL", ZEND_IS_NOT_IDENTICAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_EQUAL", ZEND_IS_EQUAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_NOT_EQUAL", ZEND_IS_NOT_EQUAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_SMALLER", ZEND_IS_SMALLER, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_IS_SMALLER_OR_EQUAL", ZEND_IS_SMALLER_OR_EQUAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_ASSIGN", ZEND_ASSIGN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_ASSIGN_OP", ZEND_ASSIGN_OP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_PRE_INC", ZEND_PRE_INC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_PRE_DEC", ZEND_PRE_DEC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_POST_INC", ZEND_POST_INC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_POST_DEC", ZEND_POST_DEC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_PRE_INC_OBJ", ZEND_PRE_INC_OBJ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_PRE_DEC_OBJ", ZEND_PRE_DEC_OBJ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_POST_INC_OBJ", ZEND_POST_INC_OBJ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_POST_DEC_OBJ", ZEND_POST_DEC_OBJ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_CAST", ZEND_CAST, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "OP_BOOL", ZEND_BOOL, CONST_CS | CONST_PERSISTENT);

    // TYPES
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_UNDEF", IS_UNDEF, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_NULL", IS_NULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_FALSE", IS_FALSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_TRUE", IS_TRUE, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT("Operators", "IS_LONG", IS_LONG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_DOUBLE", IS_DOUBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_STRING", IS_STRING, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_ARRAY", IS_ARRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_OBJECT", IS_OBJECT, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT("Operators", "IS_RESOURCE", IS_RESOURCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_REFERENCE", IS_REFERENCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT("Operators", "IS_CONSTANT_AST", IS_CONSTANT_AST, CONST_CS | CONST_PERSISTENT);
}


PHP_MINIT_FUNCTION(operators) {
	REGISTER_INI_ENTRIES();

	init_opcode_handlers_status();
	register_constants(INIT_FUNC_ARGS_PASSTHRU);
	overload_operators();

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(operators) {
	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(operators)
{
#if defined(ZTS) && defined(COMPILE_DL_OPERATORS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

PHP_RSHUTDOWN_FUNCTION(operators) {
	return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(operators)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "operators support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ operators_module_entry */
zend_module_entry operators_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_OPERATORS_EXTNAME,					/* Extension name */
	NULL,					/* zend_function_entry */
	PHP_MINIT(operators),							/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(operators),							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(operators),			/* PHP_RINIT - Request initialization */
	PHP_RSHUTDOWN(operators),							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(operators),			/* PHP_MINFO - Module info */
	PHP_OPERATORS_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPERATORS
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(operators)
#endif
