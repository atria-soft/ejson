/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/internal/Number.h>
#include <ejson/debug.h>
#include <ejson/internal/Document.h>

ememory::SharedPtr<ejson::internal::Number> ejson::internal::Number::create(double _value) {
	return ememory::SharedPtr<ejson::internal::Number>(new ejson::internal::Number(_value));
}

ejson::internal::Number::Number(double _value) :
  m_value(_value) {
	m_type = ejson::valueType::number;
}

bool ejson::internal::Number::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Number' ");
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
			EJSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> " << m_value);
			return true;
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::internal::Number::iGenerate(std::string& _data, size_t _indent) const {
	// special thing to remove .000000 at the end of perfect number ...
	int64_t tmpVal = m_value;
	if ((double)tmpVal == m_value) {
		_data += etk::to_string(tmpVal);
	} else {
		_data += etk::to_string(m_value);
	}
	return true;
}


bool ejson::internal::Number::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	if (_obj->getType() != ejson::valueType::number) {
		EJSON_ERROR("Request transfer on an element that is not an Number");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Number> other = std::static_pointer_cast<ejson::internal::Number>(_obj);
	// remove destination elements
	other->m_value = m_value;
	m_value = 0;
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Number::clone() const {
	ememory::SharedPtr<ejson::internal::Number> output = ejson::internal::Number::create(m_value);
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}

void ejson::internal::Number::set(double _value) {
	m_value = _value;
}

double ejson::internal::Number::get() const {
	return m_value;
}
