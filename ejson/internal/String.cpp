/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <ejson/internal/Document.hpp>
#include <ejson/internal/Object.hpp>
#include <ejson/internal/Array.hpp>
#include <ejson/internal/String.hpp>
#include <ejson/debug.hpp>

ememory::SharedPtr<ejson::internal::String> ejson::internal::String::create(const etk::String& _value) {
	return ememory::SharedPtr<ejson::internal::String>(ETK_NEW(ejson::internal::String, _value));
}

ejson::internal::String::String(const etk::String& _value) :
  m_value(_value) {
	m_type = ejson::valueType::String;
}

void ejson::internal::String::set(const etk::String& _value) {
	m_value = _value;
}

const etk::String& ejson::internal::String::get() const {
	return m_value;
}

bool ejson::internal::String::iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'String' ");
	char end = _data[_pos];
	bool backslashPrevious = false;
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::FilePos tmpPos;
		if(_data[iii] == '\\') {
			if (backslashPrevious == true) {
				m_value += '\\';
				backslashPrevious = false;
			} else {
				backslashPrevious = true;
			}
		} else if (_data[iii] != end) {
			if (backslashPrevious == true) {
				m_value += '\\';
				backslashPrevious = false;
			}
			m_value += _data[iii];
		} else {
			if (backslashPrevious == true) {
				m_value += '"';
				backslashPrevious = false;
			} else {
				_pos = iii;
				return true;
			}
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::internal::String::iGenerate(etk::String& _data, size_t _indent) const {
	_data += "\"";
	for (auto &it: m_value) {
		if (    it == '\\'
		     || it == '"') {
			_data += '\\';
		}
		_data += it;
	}
	_data += "\"";
	return true;
}
void ejson::internal::String::iMachineGenerate(etk::String& _data) const {
	_data += "\"";
	for (auto &it: m_value) {
		if (    it == '\\'
		     || it == '"') {
			_data += '\\';
		}
		_data += it;
	}
	_data += "\"";
}

bool ejson::internal::String::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == null) {
		EJSON_ERROR("Request transfer on an null pointer");
		return false;
	}
	if (_obj->getType() != ejson::valueType::String) {
		EJSON_ERROR("Request transfer on an element that is not an String");
		return false;
	}
	ememory::SharedPtr<ejson::internal::String> other = ememory::staticPointerCast<ejson::internal::String>(_obj);
	other->m_value = m_value;
	m_value = "";
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::String::clone() const {
	ememory::SharedPtr<ejson::internal::String> output = ejson::internal::String::create(m_value);
	if (output == null) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}


