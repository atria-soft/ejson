/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/valueType.h>
#include <ejson/debug.h>



std::ostream& ejson::operator <<(std::ostream& _os, enum ejson::valueType _obj) {
	switch (_obj) {
		case ejson::valueType::unknow:
			_os << "exml::valueType::unknow";
			break;
		case ejson::valueType::value:
			_os << "exml::valueType::value";
			break;
		case ejson::valueType::document:
			_os << "exml::valueType::document";
			break;
		case ejson::valueType::array:
			_os << "exml::valueType::array";
			break;
		case ejson::valueType::object:
			_os << "exml::valueType::object";
			break;
		case ejson::valueType::string:
			_os << "exml::valueType::string";
			break;
		case ejson::valueType::number:
			_os << "exml::valueType::number";
			break;
		case ejson::valueType::null:
			_os << "exml::valueType::null";
			break;
		case ejson::valueType::boolean:
			_os << "exml::valueType::boolean";
			break;
	}
	return _os;
}

