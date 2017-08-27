/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/valueType.hpp>
#include <ejson/debug.hpp>



etk::Stream& ejson::operator <<(etk::Stream& _os, enum ejson::valueType _obj) {
	switch (_obj) {
		case ejson::valueType::unknow:
			_os << "ejson::valueType::unknow";
			break;
		case ejson::valueType::value:
			_os << "ejson::valueType::value";
			break;
		case ejson::valueType::document:
			_os << "ejson::valueType::document";
			break;
		case ejson::valueType::array:
			_os << "ejson::valueType::array";
			break;
		case ejson::valueType::object:
			_os << "ejson::valueType::object";
			break;
		case ejson::valueType::string:
			_os << "ejson::valueType::string";
			break;
		case ejson::valueType::number:
			_os << "ejson::valueType::number";
			break;
		case ejson::valueType::null:
			_os << "ejson::valueType::null";
			break;
		case ejson::valueType::boolean:
			_os << "ejson::valueType::boolean";
			break;
	}
	return _os;
}

