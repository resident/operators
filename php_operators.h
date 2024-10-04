/* operators extension for PHP */

#ifndef PHP_OPERATORS_H
# define PHP_OPERATORS_H

extern zend_module_entry operators_module_entry;
# define phpext_operators_ptr &operators_module_entry

# define PHP_OPERATORS_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_OPERATORS)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_OPERATORS_H */
