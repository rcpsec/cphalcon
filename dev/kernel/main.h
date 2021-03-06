
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

/** Main macros */
#define PHALCON_DEBUG 0

#define PHALCON_NOISY 0
#define PHALCON_SILENT 1

#define PHALCON_CHECK 1
#define PHALCON_NO_CHECK 0

#define PHALCON_SEPARATE_PLZ 1
#define PHALCON_NO_SEPARATE_THX 0

#define PHALCON_COPY 1
#define PHALCON_NO_COPY 0

#define PHALCON_CTOR 1
#define PHALCON_NO_CTOR 0

#define PHALCON_FETCH_CLASS_SILENT (zend_bool) ZEND_FETCH_CLASS_SILENT TSRMLS_CC

/** Experimental Features **/
#define PHALCON_EXPERIMENTAL_CALL 0

/** Check whether we can use experimental call yet */
#ifdef PHP_WIN32
#define PHALCON_EXPERIMENTAL_CALL 0
#else
#if PHP_VERSION_ID < 50400
#define PHALCON_EXPERIMENTAL_CALL 0
#endif
#endif

#define SL(str) ZEND_STRL(str)

/** Exceptions */
#define PHALCON_THROW_EXCEPTION_STR(class_entry, message) phalcon_throw_exception_string(class_entry, message, strlen(message) TSRMLS_CC);

/** SPL dependencies */
#if defined(HAVE_SPL) && ((PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 1))
extern ZEND_API zend_class_entry *zend_ce_iterator;
extern ZEND_API zend_class_entry *zend_ce_arrayaccess;
extern ZEND_API zend_class_entry *zend_ce_serializable;
extern PHPAPI zend_class_entry *spl_ce_RuntimeException;
extern PHPAPI zend_class_entry *spl_ce_Countable;
extern PHPAPI zend_class_entry *spl_ce_SeekableIterator;
#endif

/** Startup functions */
extern void php_phalcon_init_globals(zend_phalcon_globals *phalcon_globals TSRMLS_DC);

/** Globals functions */
extern int phalcon_init_global(char *global, int global_length TSRMLS_DC);
extern int phalcon_get_global(zval **arr, char *global, int global_length TSRMLS_DC);
extern int phalcon_get_global_by_index(char *global, char *index, zval *result TSRMLS_DC);

/** Exception Functions */
extern void phalcon_throw_exception(zval *object TSRMLS_DC);
extern void phalcon_throw_exception_string(zend_class_entry *ce, char *message, zend_uint message_len TSRMLS_DC);

extern int phalcon_file_exists(zval *filename TSRMLS_DC);

/** Function replacement **/
extern void phalcon_fast_count(zval *result, zval *array TSRMLS_DC);
extern void phalcon_fast_join(zval *result, zval *glue, zval *pieces TSRMLS_DC);
extern void phalcon_fast_explode(zval *result, zval *delimiter, zval *str TSRMLS_DC);
extern void phalcon_fast_strpos(zval *return_value, zval *haystack, zval *needle TSRMLS_DC);
extern void phalcon_fast_str_replace(zval *return_value, zval *search, zval *replace, zval *subject TSRMLS_DC);

/** Low level filters */
extern int phalcon_filter_alphanum(zval *result, zval *param);

/* Utils functions */
extern void phalcon_inherit_not_found(char *class_name, char *inherit_name);
extern int phalcon_valid_foreach(zval *arr TSRMLS_DC);

/** Export symbols to active symbol table */
extern int phalcon_set_symbol(zval *key_name, zval *value TSRMLS_DC);

/** Compatibility with PHP 5.3 */
#ifndef ZVAL_COPY_VALUE
 #define ZVAL_COPY_VALUE(z, v)\
  (z)->value = (v)->value;\
  Z_TYPE_P(z) = Z_TYPE_P(v);
#endif

#ifndef INIT_PZVAL_COPY
 #define INIT_PZVAL_COPY(z, v) ZVAL_COPY_VALUE(z, v);\
  Z_SET_REFCOUNT_P(z, 1);\
  Z_UNSET_ISREF_P(z);
#endif

/** Symbols */
#define PHALCON_READ_SYMBOL(var, auxarr, name) if(EG(active_symbol_table)){\
			if(zend_hash_find(EG(active_symbol_table), name, sizeof(name), (void **)  &auxarr)==SUCCESS){\
				var = *auxarr;\
			} else {\
				ZVAL_NULL(var);\
			}\
		} else {\
			ZVAL_NULL(var);\
		}

#define RETURN_CHECK_CTOR(var) {\
		zend_uchar is_ref = Z_ISREF_P(return_value);\
		zend_uint refcount = Z_REFCOUNT_P(return_value);\
		*(return_value) = *(var);\
		if (Z_TYPE_P(var) > IS_BOOL) {\
			zval_copy_ctor(return_value);\
		}\
		Z_SET_ISREF_TO_P(return_value, is_ref);\
		Z_SET_REFCOUNT_P(return_value, refcount);\
	}\
	PHALCON_MM_RESTORE();\
	return;

#define RETURN_CTOR(var) {\
		zend_uchar is_ref = Z_ISREF_P(return_value);\
		zend_uint refcount = Z_REFCOUNT_P(return_value);\
		*(return_value) = *(var);\
		zval_copy_ctor(return_value);\
		Z_SET_ISREF_TO_P(return_value, is_ref);\
		Z_SET_REFCOUNT_P(return_value, refcount);\
	}\
	PHALCON_MM_RESTORE();\
	return;

#define RETURN_DZVAL(var) {\
		zend_uchar is_ref = Z_ISREF_P(return_value);\
		zend_uint refcount = Z_REFCOUNT_P(return_value);\
		*(return_value) = *(var);\
		zval_copy_ctor(return_value);\
		Z_SET_ISREF_TO_P(return_value, is_ref);\
		Z_SET_REFCOUNT_P(return_value, refcount);\
		PHALCON_MM_RESTORE();\
	}\
	return;

#define RETURN_NCTOR(var) {\
		zend_uchar is_ref = Z_ISREF_P(return_value);\
		zend_uint refcount = Z_REFCOUNT_P(return_value);\
		*(return_value) = *(var);\
		Z_SET_ISREF_TO_P(return_value, is_ref);\
		Z_SET_REFCOUNT_P(return_value, refcount);\
	}\
	PHALCON_MM_RESTORE();\
	return;

/** Foreach */
#define PHALCON_GET_FOREACH_KEY(var, hash, hash_pointer) \
	hash_type = zend_hash_get_current_key_ex(hash, &hash_index, &hash_index_len, &hash_num, 0, &hash_pointer); \
	if (hash_type == HASH_KEY_IS_STRING) { \
		ZVAL_STRINGL(var, hash_index, hash_index_len-1, 1); \
	} else { \
		if (hash_type == HASH_KEY_IS_LONG) { \
			ZVAL_LONG(var, hash_num); \
		}\
	}

