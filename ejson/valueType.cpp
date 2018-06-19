/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/valueType.hpp>
#include <ejson/debug.hpp>



etk::Stream& ejson::operator <<(etk::Stream& _os, enum ejson::valueType _obj) {
	switch (_obj) {
		case ejson::valueType::Unknow:
			_os << "ejson::valueType::Unknow";
			break;
		case ejson::valueType::Value:
			_os << "ejson::valueType::Value";
			break;
		case ejson::valueType::Document:
			_os << "ejson::valueType::Document";
			break;
		case ejson::valueType::Array:
			_os << "ejson::valueType::Array";
			break;
		case ejson::valueType::Object:
			_os << "ejson::valueType::Object";
			break;
		case ejson::valueType::String:
			_os << "ejson::valueType::String";
			break;
		case ejson::valueType::Number:
			_os << "ejson::valueType::Number";
			break;
		case ejson::valueType::Null:
			_os << "ejson::valueType::Null";
			break;
		case ejson::valueType::Boolean:
			_os << "ejson::valueType::Boolean";
			break;
	}
	return _os;
}

