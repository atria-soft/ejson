/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <ejson/Boolean.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Boolean"

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


bool ejson::Boolean::transfertIn(ejson::Value* _obj) {
	if (NULL == _obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Boolean* other = _obj->toBoolean();
	if (NULL == other) {
		JSON_ERROR("Request transfer on an element that is not an Boolean");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = false;
	return true;
}

ejson::Value* ejson::Boolean::duplicate() const {
	ejson::Boolean* output = new ejson::Boolean(m_value);
	if (NULL == output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	return output;
}


