/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <ejson/debug.h>

int32_t ejson::getLogId(void) {
	static int32_t g_val = etk::log::registerInstance("ejson");
	return g_val;
}

