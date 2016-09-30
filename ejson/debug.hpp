/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <elog/log.hpp>

namespace ejson {
	int32_t getLogId();
};
#define EJSON_BASE(info,data)  ELOG_BASE(ejson::getLogId(),info,data)

#define EJSON_CRITICAL(data)      EJSON_BASE(1, data)
#define EJSON_ERROR(data)         EJSON_BASE(2, data)
#define EJSON_WARNING(data)       EJSON_BASE(3, data)
#ifdef DEBUG
	#define EJSON_INFO(data)          EJSON_BASE(4, data)
	#define EJSON_DEBUG(data)         EJSON_BASE(5, data)
	#define EJSON_VERBOSE(data)       EJSON_BASE(6, data)
	#define EJSON_TODO(data)          EJSON_BASE(4, "TODO : " << data)
#else
	#define EJSON_INFO(data)          do { } while(false)
	#define EJSON_DEBUG(data)         do { } while(false)
	#define EJSON_VERBOSE(data)       do { } while(false)
	#define EJSON_TODO(data)          do { } while(false)
#endif

#define EJSON_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			JSON_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

