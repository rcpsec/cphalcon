
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
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
/**
 * Array_Paginator
 *
 * Component of pagination by array data
 *
 */

/**
     * Phalcon_Paginator_Adapter_Array constructor
  *
 * @param array $config
     */
PHP_METHOD(Phalcon_Paginator_Adapter_Array, __construct){

	zval *config = NULL;
	zval *r0 = NULL, *r1 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &config) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_config"), config TSRMLS_CC);
	eval_int = phalcon_array_isset_string(config, SL("limit")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, config, SL("limit"), PHALCON_NOISY TSRMLS_CC);
		phalcon_update_property_zval(this_ptr, SL("_limitRows"), r0 TSRMLS_CC);
	}
	
	eval_int = phalcon_array_isset_string(config, SL("page")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r1);
		phalcon_array_fetch_string(&r1, config, SL("page"), PHALCON_NOISY TSRMLS_CC);
		phalcon_update_property_zval(this_ptr, SL("_page"), r1 TSRMLS_CC);
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Set the current page number
 *
 * @param int $page
 */
PHP_METHOD(Phalcon_Paginator_Adapter_Array, setCurrentPage){

	zval *page = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &page) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_page"), page TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns a slice of the resultset to show in the pagination
 *
 * @return stdClass
 */
PHP_METHOD(Phalcon_Paginator_Adapter_Array, getPaginate){

	zval *show = NULL, *items = NULL, *page_number = NULL, *n = NULL, *page = NULL, *start = NULL, *total_pages = NULL;
	zval *next = NULL, *before = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL, *t6 = NULL;
	zval *t7 = NULL, *t8 = NULL, *t9 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL, *r11 = NULL, *r12 = NULL, *r13 = NULL;
	zval *r14 = NULL, *r15 = NULL, *r16 = NULL, *r17 = NULL, *r18 = NULL, *r19 = NULL, *r20 = NULL;
	zval *r21 = NULL, *r22 = NULL, *r23 = NULL, *r24 = NULL;
	zval *i0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_limitRows"), PHALCON_NOISY TSRMLS_CC);
	PHALCON_CPY_WRT(show, t0);
	
	PHALCON_ALLOC_ZVAL_MM(t1);
	phalcon_read_property(&t1, this_ptr, SL("_config"), PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	phalcon_array_fetch_string(&r0, t1, SL("data"), PHALCON_NOISY TSRMLS_CC);
	PHALCON_CPY_WRT(items, r0);
	
	PHALCON_ALLOC_ZVAL_MM(t2);
	phalcon_read_property(&t2, this_ptr, SL("_page"), PHALCON_NOISY TSRMLS_CC);
	PHALCON_CPY_WRT(page_number, t2);
	if (Z_TYPE_P(page_number) == IS_NULL) {
		PHALCON_INIT_VAR(page_number);
		ZVAL_LONG(page_number, 1);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	phalcon_fast_count(r1, items TSRMLS_CC);
	PHALCON_CPY_WRT(n, r1);
	
	PHALCON_ALLOC_ZVAL_MM(i0);
	object_init(i0);
	PHALCON_CPY_WRT(page, i0);
	
	PHALCON_INIT_VAR(t3);
	ZVAL_LONG(t3, 1);
	
	PHALCON_ALLOC_ZVAL_MM(r2);
	sub_function(r2, page_number, t3 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r3);
	mul_function(r3, show, r2 TSRMLS_CC);
	PHALCON_CPY_WRT(start, r3);
	
	PHALCON_ALLOC_ZVAL_MM(r4);
	phalcon_fast_count(r4, items TSRMLS_CC);
	
	PHALCON_INIT_VAR(t4);
	ZVAL_LONG(t4, 1);
	
	PHALCON_ALLOC_ZVAL_MM(r5);
	sub_function(r5, r4, t4 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r6);
	div_function(r6, r5, show TSRMLS_CC);
	
	PHALCON_INIT_VAR(total_pages);
	PHALCON_CALL_FUNC_PARAMS_1(total_pages, "round", r6);
	if (Z_TYPE_P(items) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_paginator_exception_ce, "Invalid data for paginator");
		return;
	}
	
	PHALCON_ALLOC_ZVAL_MM(r7);
	PHALCON_CALL_FUNC_PARAMS_3(r7, "array_slice", items, start, show);
	phalcon_update_property_zval(page, SL("items"), r7 TSRMLS_CC);
	phalcon_update_property_long(page, SL("first"), 1 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r8);
	phalcon_add_function(r8, start, show TSRMLS_CC);
	
	PHALCON_INIT_VAR(r9);
	is_smaller_function(r9, r8, n TSRMLS_CC);
	if (zend_is_true(r9)) {
		PHALCON_INIT_VAR(t5);
		ZVAL_LONG(t5, 1);
		PHALCON_ALLOC_ZVAL_MM(r10);
		phalcon_add_function(r10, page_number, t5 TSRMLS_CC);
		PHALCON_CPY_WRT(next, r10);
	} else {
		PHALCON_ALLOC_ZVAL_MM(r11);
		phalcon_add_function(r11, start, show TSRMLS_CC);
		PHALCON_ALLOC_ZVAL_MM(r12);
		is_equal_function(r12, r11, n TSRMLS_CC);
		if (zend_is_true(r12)) {
			PHALCON_CPY_WRT(next, n);
		} else {
			PHALCON_ALLOC_ZVAL_MM(r13);
			PHALCON_ALLOC_ZVAL_MM(r14);
			div_function(r14, n, show TSRMLS_CC);
			phalcon_cast(r13, r14, IS_LONG);
			PHALCON_INIT_VAR(t6);
			ZVAL_LONG(t6, 1);
			PHALCON_ALLOC_ZVAL_MM(r15);
			phalcon_add_function(r15, r13, t6 TSRMLS_CC);
			PHALCON_CPY_WRT(next, r15);
		}
	}
	
	PHALCON_INIT_VAR(r16);
	is_smaller_function(r16, total_pages, next TSRMLS_CC);
	if (zend_is_true(r16)) {
		PHALCON_CPY_WRT(next, total_pages);
	}
	
	phalcon_update_property_zval(page, SL("next"), next TSRMLS_CC);
	
	PHALCON_INIT_VAR(t7);
	ZVAL_LONG(t7, 1);
	
	PHALCON_INIT_VAR(r17);
	is_smaller_function(r17, t7, page_number TSRMLS_CC);
	if (zend_is_true(r17)) {
		PHALCON_INIT_VAR(t8);
		ZVAL_LONG(t8, 1);
		PHALCON_ALLOC_ZVAL_MM(r18);
		sub_function(r18, page_number, t8 TSRMLS_CC);
		PHALCON_CPY_WRT(before, r18);
	} else {
		PHALCON_INIT_VAR(before);
		ZVAL_LONG(before, 1);
	}
	
	phalcon_update_property_zval(page, SL("before"), before TSRMLS_CC);
	phalcon_update_property_zval(page, SL("current"), page_number TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r20);
	mod_function(r20, n, show TSRMLS_CC);
	if (zend_is_true(r20)) {
		PHALCON_ALLOC_ZVAL_MM(r21);
		
		PHALCON_ALLOC_ZVAL_MM(r22);
		div_function(r22, n, show TSRMLS_CC);
		phalcon_cast(r21, r22, IS_LONG);
		
		PHALCON_INIT_VAR(t9);
		ZVAL_LONG(t9, 1);
		
		PHALCON_ALLOC_ZVAL_MM(r23);
		phalcon_add_function(r23, r21, t9 TSRMLS_CC);
		r19 = r23;
	} else {
		
		PHALCON_ALLOC_ZVAL_MM(r24);
		div_function(r24, n, show TSRMLS_CC);
		r19 = r24;
	}
	PHALCON_CPY_WRT(total_pages, r19);
	phalcon_update_property_zval(page, SL("last"), total_pages TSRMLS_CC);
	phalcon_update_property_zval(page, SL("total_pages"), total_pages TSRMLS_CC);
	
	RETURN_CTOR(page);
}

