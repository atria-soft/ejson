/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <elog/log.h>

namespace ejson {
	int32_t getLogId();
};
#define JSON_BASE(info,data)  ELOG_BASE(ejson::getLogId(),info,data)

#define JSON_CRITICAL(data)      JSON_BASE(1, data)
#define JSON_ERROR(data)         JSON_BASE(2, data)
#define JSON_WARNING(data)       JSON_BASE(3, data)
#ifdef DEBUG
	#define JSON_INFO(data)          JSON_BASE(4, data)
	#define JSON_DEBUG(data)         JSON_BASE(5, data)
	#define JSON_VERBOSE(data)       JSON_BASE(6, data)
	#define JSON_TODO(data)          JSON_BASE(4, "TODO : " << data)
#else
	#define JSON_INFO(data)          do { } while(false)
	#define JSON_DEBUG(data)         do { } while(false)
	#define JSON_VERBOSE(data)       do { } while(false)
	#define JSON_TODO(data)          do { } while(false)
#endif

#define JSON_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			JSON_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

