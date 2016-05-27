/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>

namespace ejson {
	namespace base64 {
		std::string encode(const uint8_t* _data, int32_t _len);
		std::vector<uint8_t> decode(const std::string& _data);
	}
}
