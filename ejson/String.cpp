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



bool ejson::String::iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'String' ");
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		// TODO : manage \x
		if(    _data[iii]!= '\"') {
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


bool ejson::String::transfertIn(ejson::Value* _obj) {
	if (NULL == _obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::String* other = _obj->toString();
	if (NULL == other) {
		JSON_ERROR("Request transfer on an element that is not an String");
		return false;
	}
	other->m_value = m_value;
	m_value = "";
	return true;
}

ejson::Value* ejson::String::duplicate() const {
	ejson::String* output = new ejson::String(m_value);
	if (NULL == output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	return output;
}


