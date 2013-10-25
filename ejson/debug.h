/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EJSON_DEBUG_H__
#define __EJSON_DEBUG_H__

#include <etk/types.h>
#include <etk/debugGeneric.h>

extern const char * g_ejsonLibName;

#define JSON_CRITICAL(data)			ETK_CRITICAL(g_ejsonLibName, data)
#define JSON_WARNING(data)			ETK_WARNING(g_ejsonLibName, data)
#define JSON_ERROR(data)			ETK_ERROR(g_ejsonLibName, data)
#define JSON_INFO(data)				ETK_INFO(g_ejsonLibName, data)
#define JSON_DEBUG(data)			ETK_DEBUG(g_ejsonLibName, data)
#define JSON_VERBOSE(data)			ETK_VERBOSE(g_ejsonLibName, data)
#define JSON_ASSERT(cond, data)		ETK_ASSERT(g_ejsonLibName, cond, data)
#define JSON_CHECK_INOUT(cond)		ETK_CHECK_INOUT(g_ejsonLibName, cond)
#define JSON_TODO(cond)				ETK_TODO(g_ejsonLibName, cond)

#endif
