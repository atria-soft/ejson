/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <ejson/Number.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Number"

bool ejson::Number::iParse(const std::string& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Number' ");
	std::string tmpVal;
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if(true == checkNumber(_data[iii])) {
			tmpVal+=_data[iii];
		} else {
			_pos = iii-1;
			m_value = std::stod(tmpVal);
			JSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> " << m_value);
			return true;
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::Number::iGenerate(std::string& _data, int32_t _indent) const {
	// special thing to remove .000000 at the end of perfect number ...
	int64_t tmpVal = m_value;
	if ((double)tmpVal == m_value) {
		_data += std::to_string(tmpVal);
	} else {
		_data += std::to_string(m_value);
	}
	return true;
}


bool ejson::Number::transfertIn(ejson::Value* _obj) {
	if (NULL == _obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Number* other = _obj->toNumber();
	if (NULL == other) {
		JSON_ERROR("Request transfer on an element that is not an Number");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = 0;
	return true;
}

ejson::Value* ejson::Number::duplicate(void) const {
	ejson::Number* output = new ejson::Number(m_value);
	if (NULL == output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	return output;
}


