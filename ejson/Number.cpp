/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/Number.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Number"

std::shared_ptr<ejson::Number> ejson::Number::create(double _value) {
	return std::shared_ptr<ejson::Number>(new ejson::Number(_value));
}

bool ejson::Number::iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Number' ");
	std::string tmpVal;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if(true == checkNumber(_data[iii])) {
			tmpVal+=_data[iii];
		} else {
			_pos = iii-1;
			m_value = etk::string_to_double(tmpVal);
			JSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> " << m_value);
			return true;
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::Number::iGenerate(std::string& _data, size_t _indent) const {
	// special thing to remove .000000 at the end of perfect number ...
	int64_t tmpVal = m_value;
	if ((double)tmpVal == m_value) {
		_data += etk::to_string(tmpVal);
	} else {
		_data += etk::to_string(m_value);
	}
	return true;
}


bool ejson::Number::transfertIn(std::shared_ptr<ejson::Value> _obj) {
	if (_obj == nullptr) {
		JSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	std::shared_ptr<ejson::Number> other = _obj->toNumber();
	if (other == nullptr) {
		JSON_ERROR("Request transfer on an element that is not an Number");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = 0;
	return true;
}

std::shared_ptr<ejson::Value> ejson::Number::clone() const {
	std::shared_ptr<ejson::Number> output = ejson::Number::create(m_value);
	if (output == nullptr) {
		JSON_ERROR("Allocation error ...");
		return std::shared_ptr<ejson::Value>();
	}
	return output;
}


