/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"String"


std11::shared_ptr<ejson::String> ejson::String::create(const std::string& _value) {
	return std11::shared_ptr<ejson::String>(new ejson::String(_value));
}

bool ejson::String::iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'String' ");
	char end = _data[_pos];
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		// TODO : manage \x
		if(_data[iii] != end) {
			m_value += _data[iii];
		} else {
			_pos = iii;
			return true;
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::String::iGenerate(std::string& _data, size_t _indent) const {
	_data += "\"";;
	_data += m_value;
	_data += "\"";;
	return true;
}


bool ejson::String::transfertIn(std11::shared_ptr<ejson::Value> _obj) {
	if (_obj == nullptr) {
		JSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	std11::shared_ptr<ejson::String> other = _obj->toString();
	if (other == nullptr) {
		JSON_ERROR("Request transfer on an element that is not an String");
		return false;
	}
	other->m_value = m_value;
	m_value = "";
	return true;
}

std11::shared_ptr<ejson::Value> ejson::String::clone() const {
	std11::shared_ptr<ejson::String> output = ejson::String::create(m_value);
	if (output == nullptr) {
		JSON_ERROR("Allocation error ...");
		return std11::shared_ptr<ejson::Value>();
	}
	return output;
}


