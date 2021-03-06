#include "joomla.h"
#include "ext/standard/php_var.h"
#include "zend.h"

// This bit of code is to detect the presence of Joomla
// and extract the abstract path

int hasJoomla(TSRMLS_D)
{
    if(zend_hash_exists(EG(class_table), "japplication", sizeof("japplication")) 
        && zend_hash_exists(EG(class_table), "jfactory", sizeof("jfactory")) )
    {
        return 1;
    }
    return 0;
}

char* getJoomlaPath(size_t *slen TSRMLS_DC)
{
    char* result;
    zval retval;
    if(zend_eval_string("(isset($_REQUEST['option']) && isset($_REQUEST['view']) ?  ($_REQUEST['option'].'::'.$_REQUEST['view']) : NULL);", &retval, "graphdat joomla" TSRMLS_CC) == FAILURE)
    {
        return NULL;
    }
    result = Z_STRVAL_P(&retval);
    *slen = Z_STRLEN_P(&retval);
    return result;
}
