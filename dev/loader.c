
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

#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/require.h"
#include "kernel/concat.h"
/**
 * Phalcon_Loader
 *
 * This component helps to load your project classes automatically based on some conventions
 *
 *
 */

PHP_METHOD(Phalcon_Loader, __construct){

	zval *a0 = NULL, *a1 = NULL;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(a0);
	array_init(a0);
	zend_update_property(phalcon_loader_ce, this_ptr, SL("_namespaces"), a0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(a1);
	array_init(a1);
	zend_update_property(phalcon_loader_ce, this_ptr, SL("_directories"), a1 TSRMLS_CC);

	PHALCON_MM_RESTORE();
}

/**
 * Register namespaces and their related directories
 *
 * @param array $namespaces
 */
PHP_METHOD(Phalcon_Loader, registerNamespaces){

	zval *namespaces = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &namespaces) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(namespaces) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_loader_exception_ce, "Parameter namespaces must be an Array");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_namespaces"), namespaces TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Register directories on which "not found" classes could be found
 *
 * @param array $directories
 */
PHP_METHOD(Phalcon_Loader, registerDirs){

	zval *directories = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &directories) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(directories) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_loader_exception_ce, "Parameter directories must be an Array");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_directories"), directories TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Register classes and their locations
 *
 * @param array $directories
 */
PHP_METHOD(Phalcon_Loader, registerClasses){

	zval *classes = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &classes) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(classes) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_loader_exception_ce, "Parameter classes must be an Array");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_classes"), classes TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Register the autoload method
 */
PHP_METHOD(Phalcon_Loader, register){

	zval *a0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(a0);
	array_init(a0);
	phalcon_array_append(&a0, this_ptr, PHALCON_SEPARATE_PLZ TSRMLS_CC);
	add_next_index_stringl(a0, SL("autoLoad"), 1);
	PHALCON_CALL_FUNC_PARAMS_1_NORETURN("spl_autoload_register", a0);
	
	PHALCON_MM_RESTORE();
}

/**
 * Makes the work of autoload registered classes
 *
 * @param string $className
 * @return boolean
 */
PHP_METHOD(Phalcon_Loader, autoLoad){

	zval *class_name = NULL, *file_name = NULL, *directory = NULL, *preffix = NULL;
	zval *path = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL;
	zval *c0 = NULL, *c1 = NULL, *c2 = NULL;
	HashTable *ah0, *ah1;
	HashPosition hp0, hp1;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &class_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_classes"), PHALCON_NOISY TSRMLS_CC);
	eval_int = phalcon_array_isset(t0, class_name);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t1);
		phalcon_read_property(&t1, this_ptr, SL("_classes"), PHALCON_NOISY TSRMLS_CC);
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch(&r0, t1, class_name, PHALCON_NOISY TSRMLS_CC);
		PHALCON_CPY_WRT(file_name, r0);
		if (phalcon_require(file_name TSRMLS_CC) == FAILURE) {
			return;
		}
		PHALCON_MM_RESTORE();
		RETURN_TRUE;
	}
	
	PHALCON_ALLOC_ZVAL_MM(t2);
	phalcon_read_property(&t2, this_ptr, SL("_namespaces"), PHALCON_NOISY TSRMLS_CC);
	if (phalcon_valid_foreach(t2 TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(t2);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_0c08_0:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_0c08_0;
		} else {
			PHALCON_INIT_VAR(preffix);
			PHALCON_GET_FOREACH_KEY(preffix, ah0, hp0);
		}
		PHALCON_INIT_VAR(directory);
		ZVAL_ZVAL(directory, *hd, 1, 0);
		PHALCON_INIT_VAR(r1);
		PHALCON_CALL_FUNC_PARAMS_1(r1, "strlen", class_name);
		PHALCON_INIT_VAR(r2);
		is_smaller_function(r2, preffix, r1 TSRMLS_CC);
		if (zend_is_true(r2)) {
			PHALCON_INIT_VAR(c0);
			ZVAL_LONG(c0, 0);
			PHALCON_INIT_VAR(r3);
			PHALCON_CALL_FUNC_PARAMS_1(r3, "strlen", preffix);
			PHALCON_INIT_VAR(r4);
			PHALCON_CALL_FUNC_PARAMS_3(r4, "substr", class_name, c0, r3);
			PHALCON_INIT_VAR(r5);
			is_equal_function(r5, r4, preffix TSRMLS_CC);
			if (zend_is_true(r5)) {
				PHALCON_INIT_VAR(r6);
				PHALCON_CONCAT_VS(r6, preffix, "\\");
				PHALCON_INIT_VAR(c1);
				ZVAL_STRING(c1, "", 1);
				PHALCON_INIT_VAR(r7);
				phalcon_fast_str_replace(r7, r6, c1, class_name TSRMLS_CC);
				PHALCON_CPY_WRT(file_name, r7);
				if (zend_is_true(file_name)) {
					PHALCON_INIT_VAR(c2);
					ZVAL_STRING(c2, "\\", 1);
					PHALCON_INIT_VAR(t3);
					zend_get_constant("DIRECTORY_SEPARATOR", strlen("DIRECTORY_SEPARATOR"), t3 TSRMLS_CC);
					PHALCON_INIT_VAR(r8);
					PHALCON_CONCAT_VVS(r8, directory, file_name, ".php");
					PHALCON_INIT_VAR(r9);
					phalcon_fast_str_replace(r9, c2, t3, r8 TSRMLS_CC);
					PHALCON_CPY_WRT(path, r9);
					if (phalcon_file_exists(path TSRMLS_CC) == SUCCESS) {
						if (phalcon_require(path TSRMLS_CC) == FAILURE) {
							return;
						}
						PHALCON_MM_RESTORE();
						RETURN_TRUE;
					}
				}
			}
		}
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_0c08_0;
		fee_0c08_0:
		if(0){}
	} else {
		return;
	}
	
	PHALCON_ALLOC_ZVAL_MM(t4);
	phalcon_read_property(&t4, this_ptr, SL("_directories"), PHALCON_NOISY TSRMLS_CC);
	if (phalcon_valid_foreach(t4 TSRMLS_CC)) {
		ah1 = Z_ARRVAL_P(t4);
		zend_hash_internal_pointer_reset_ex(ah1, &hp1);
		fes_0c08_1:
		if(zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) != SUCCESS){
			goto fee_0c08_1;
		}
		
		PHALCON_INIT_VAR(directory);
		ZVAL_ZVAL(directory, *hd, 1, 0);
		PHALCON_INIT_VAR(r10);
		PHALCON_CONCAT_VVS(r10, directory, class_name, ".php");
		PHALCON_CPY_WRT(path, r10);
		if (phalcon_file_exists(path TSRMLS_CC) == SUCCESS) {
			if (phalcon_require(path TSRMLS_CC) == FAILURE) {
				return;
			}
			PHALCON_MM_RESTORE();
			RETURN_TRUE;
		}
		zend_hash_move_forward_ex(ah1, &hp1);
		goto fes_0c08_1;
		fee_0c08_1:
		if(0){}
	} else {
		return;
	}
	
	PHALCON_MM_RESTORE();
}

