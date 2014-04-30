/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EJSON_DEBUG_H__
#define __EJSON_DEBUG_H__

#include <etk/log.h>

namespace ejson {
	int32_t getLogId(void);
};
// TODO : Review this problem of multiple intanciation of "std::stringbuf sb"
#define JSON_BASE(info,data) \
	do { \
		if (info <= etk::log::getLevel(ejson::getLogId())) { \
			std::stringbuf sb; \
			std::ostream tmpStream(&sb); \
			tmpStream << data; \
			etk::log::logStream(ejson::getLogId(), info, __LINE__, __class__, __func__, tmpStream); \
		} \
	} while(0)

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

#endif
