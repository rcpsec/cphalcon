
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/fcall.h"
#include "kernel/concat.h"
/**
 * Phalcon_Utils
 *
 * Implements functionality used widely by the framework
 */

/**
 * This function is now deprecated, use Phalcon_Text::camelize instead
 *
 * @param string $str
 * @return string
 */
PHP_METHOD(Phalcon_Utils, camelize){

	zval *str = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &str) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_STATIC_PARAMS_1(r0, "phalcon_text", "camelize", str);
	RETURN_DZVAL(r0);
}

/**
 * This function is now deprecated, use Phalcon_Text::uncamelize instead
 *
 * @param string $str
 * @return string
 */
PHP_METHOD(Phalcon_Utils, uncamelize){

	zval *str = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &str) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_STATIC_PARAMS_1(r0, "phalcon_text", "uncamelize", str);
	RETURN_DZVAL(r0);
}

/**
 * Gets public URL to phalcon instance
 *
 * @param string $uri
 * @return string
 */
PHP_METHOD(Phalcon_Utils, getUrl){

	zval *uri = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &uri) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!uri) {
		PHALCON_INIT_VAR(uri);
		ZVAL_NULL(uri);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_ALLOC_ZVAL_MM(r2);
	PHALCON_CALL_STATIC(r2, "phalcon_controller_front", "getinstance");
	PHALCON_CALL_METHOD(r1, r2, "getbaseuri", PHALCON_NO_CHECK);
	PHALCON_CONCAT_VV(r0, r1, uri);
	
	RETURN_CTOR(r0);
}

/**
 * Gets path to local file
 *
 * @param string $extraPath
 * @return string
 */
PHP_METHOD(Phalcon_Utils, getLocalPath){

	zval *extra_path = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &extra_path) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!extra_path) {
		PHALCON_INIT_VAR(extra_path);
		ZVAL_NULL(extra_path);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_ALLOC_ZVAL_MM(r2);
	PHALCON_CALL_STATIC(r2, "phalcon_controller_front", "getinstance");
	PHALCON_CALL_METHOD(r1, r2, "getbasepath", PHALCON_NO_CHECK);
	PHALCON_CONCAT_VV(r0, r1, extra_path);
	
	RETURN_CTOR(r0);
}

