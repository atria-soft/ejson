/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/internal/Boolean.h>
#include <ejson/debug.h>
#include <ejson/internal/Document.h>

ememory::SharedPtr<ejson::internal::Boolean> ejson::internal::Boolean::create(bool _value) {
	return ememory::SharedPtr<ejson::internal::Boolean>(new ejson::internal::Boolean(_value));
}


bool ejson::internal::Boolean::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Boolean' ");
	m_value=false;
	if(    _data[_pos] == 't'
	    && _pos+3 < _data.size()
	    && _data[_pos+1] == 'r'
	    && _data[_pos+2] == 'u'
	    && _data[_pos+3] == 'e'){
		m_value=true;
		_pos+=3;
		_filePos+=3;
		return true;
	}
	if(    _data[_pos] == 'f'
	    && _pos+4 < _data.size()
	    && _data[_pos+1] == 'a'
	    && _data[_pos+2] == 'l'
	    && _data[_pos+3] == 's'
	    && _data[_pos+4] == 'e'){
		m_value=false;
		_pos+=4;
		_filePos+=4;
		return true;
	}
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "boolean parsing error ...");
	return false;
}


bool ejson::internal::Boolean::iGenerate(std::string& _data, size_t _indent) const {
	if (true == m_value) {
		_data += "true";
	} else {
		_data += "false";
	}
	return true;
}


bool ejson::internal::Boolean::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Boolean> other = _obj->toBoolean();
	if (other == nullptr) {
		EJSON_ERROR("Request transfer on an element that is not an Boolean");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = false;
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Boolean::clone() const {
	ememory::SharedPtr<ejson::internal::Boolean> output = ejson::internal::Boolean::create(m_value);
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}


