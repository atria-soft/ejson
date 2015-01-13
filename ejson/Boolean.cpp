/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/Boolean.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Boolean"

std::shared_ptr<ejson::Boolean> ejson::Boolean::create(bool _value) {
	return std::shared_ptr<ejson::Boolean>(new ejson::Boolean(_value));
}


bool ejson::Boolean::iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Boolean' ");
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


bool ejson::Boolean::iGenerate(std::string& _data, size_t _indent) const {
	if (true == m_value) {
		_data += "true";
	} else {
		_data += "false";
	}
	return true;
}


bool ejson::Boolean::transfertIn(std::shared_ptr<ejson::Value> _obj) {
	if (_obj == nullptr) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	std::shared_ptr<ejson::Boolean> other = _obj->toBoolean();
	if (other == nullptr) {
		JSON_ERROR("Request transfer on an element that is not an Boolean");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = false;
	return true;
}

std::shared_ptr<ejson::Value> ejson::Boolean::clone() const {
	std::shared_ptr<ejson::Boolean> output = ejson::Boolean::create(m_value);
	if (output == nullptr) {
		JSON_ERROR("Allocation error ...");
		return nullptr;
	}
	return output;
}


