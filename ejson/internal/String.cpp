/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/internal/Document.h>
#include <ejson/internal/Object.h>
#include <ejson/internal/Array.h>
#include <ejson/internal/String.h>
#include <ejson/debug.h>

ememory::SharedPtr<ejson::internal::String> ejson::internal::String::create(const std::string& _value) {
	return ememory::SharedPtr<ejson::internal::String>(new ejson::internal::String(_value));
}

bool ejson::internal::String::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'String' ");
	char end = _data[_pos];
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::FilePos tmpPos;
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


bool ejson::internal::String::iGenerate(std::string& _data, size_t _indent) const {
	_data += "\"";;
	_data += m_value;
	_data += "\"";;
	return true;
}


bool ejson::internal::String::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	ememory::SharedPtr<ejson::internal::String> other = _obj->toString();
	if (other == nullptr) {
		EJSON_ERROR("Request transfer on an element that is not an String");
		return false;
	}
	other->m_value = m_value;
	m_value = "";
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::String::clone() const {
	ememory::SharedPtr<ejson::internal::String> output = ejson::internal::String::create(m_value);
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}


