/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/debug.hpp>

int32_t ejson::getLogId() {
	static int32_t g_val = elog::registerInstance("ejson");
	return g_val;
}

