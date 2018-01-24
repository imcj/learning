/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hackable.h"
#include <sys/socket.h>
#include "poll.h"

/* If you declare any globals in php_hackable.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(hackable)
*/

/* True global resources - no need for thread safety here */
static int le_hackable;
#define le_hackable_name "Hackable"

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("hackable.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_hackable_globals, hackable_globals)
    STD_PHP_INI_ENTRY("hackable.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_hackable_globals, hackable_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_hackable_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_hackable_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "hackable", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(hackable_socket)
{
	// int socketfd;mtfd);
}


PHP_FUNCTION(hackable_poll)
{
	zend_long s;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &s) == FAILURE) {
		return;
	}
	RETURN_LONG(s);
}

PHP_FUNCTION(fd_set_new)
{
	long max;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &max) == FAILURE) {
        RETURN_FALSE;
    }
	struct pollfd *pollfds;
	pollfds = malloc(sizeof(struct pollfd) * max);
	RETURN_RES(zend_register_resource(pollfds, le_hackable));
}

PHP_FUNCTION(fd_get)
{
	// if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &max) == FAILURE) {
    //     RETURN_FALSE;
    // }
}

void php_destory_hackable(zend_resource *rsrc)
{

}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_hackable_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_hackable_init_globals(zend_hackable_globals *hackable_globals)
{
	hackable_globals->global_value = 0;
	hackable_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(hackable)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	le_hackable = zend_register_list_destructors_ex(NULL, NULL, le_hackable_name, module_number);

	REGISTER_LONG_CONSTANT("H_POLLIN",	POLLIN,	CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("H_POLLOUT",	POLLOUT,	CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hackable)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(hackable)
{
#if defined(COMPILE_DL_HACKABLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(hackable)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(hackable)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "hackable support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ hackable_functions[]
 *
 * Every user visible function must have an entry in hackable_functions[].
 */
const zend_function_entry hackable_functions[] = {
	PHP_FE(confirm_hackable_compiled,	NULL)		/* For testing, remove later. */
        PHP_FE(hackable_poll, NULL)
	PHP_FE_END	/* Must be the last line in hackable_functions[] */
};
/* }}} */

/* {{{ hackable_module_entry
 */
zend_module_entry hackable_module_entry = {
	STANDARD_MODULE_HEADER,
	"hackable",
	hackable_functions,
	PHP_MINIT(hackable),
	PHP_MSHUTDOWN(hackable),
	PHP_RINIT(hackable),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(hackable),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(hackable),
	PHP_HACKABLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HACKABLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(hackable)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
