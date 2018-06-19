/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <ejson/internal/Number.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Document.hpp>

ememory::SharedPtr<ejson::internal::Number> ejson::internal::Number::create(double _value) {
	return ememory::SharedPtr<ejson::internal::Number>(ETK_NEW(ejson::internal::Number, _value));
}
ememory::SharedPtr<ejson::internal::Number> ejson::internal::Number::create(uint64_t _value) {
	return ememory::SharedPtr<ejson::internal::Number>(ETK_NEW(ejson::internal::Number, _value));
}
ememory::SharedPtr<ejson::internal::Number> ejson::internal::Number::create(int64_t _value) {
	return ememory::SharedPtr<ejson::internal::Number>(ETK_NEW(ejson::internal::Number, _value));
}

ejson::internal::Number::Number(double _value) :
  m_typeNumber(ejson::internal::Number::type::tDouble),
  m_value(_value) {
	m_type = ejson::valueType::Number;
}

ejson::internal::Number::Number(uint64_t _value) :
  m_typeNumber(ejson::internal::Number::type::tUint),
  m_valueU64(_value) {
	m_type = ejson::valueType::Number;
}

ejson::internal::Number::Number(int64_t _value) :
  m_typeNumber(ejson::internal::Number::type::tInt),
  m_valueI64(_value) {
	m_type = ejson::valueType::Number;
}

bool ejson::internal::Number::iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Number' ");
	etk::String tmpVal;
	bool isDouble = false;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if(checkNumber(_data[iii]) == true) {
			if (    _data[iii] == '.'
			     || _data[iii] == 'e'
			     || _data[iii] == '^') {
				isDouble = true;
			}
			tmpVal+=_data[iii];
		} else {
			_pos = iii-1;
			if (isDouble == true) {
				m_typeNumber = ejson::internal::Number::type::tDouble;
				m_value = etk::string_to_double(tmpVal);
				EJSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> double=" << m_value);
			} else if (tmpVal[0] == '-') {
				m_typeNumber = ejson::internal::Number::type::tInt;
				m_valueI64 = etk::string_to_double(tmpVal);
				EJSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> int64_t=" << m_valueI64);
			} else {
				m_typeNumber = ejson::internal::Number::type::tUint;
				m_valueU64 = etk::string_to_double(tmpVal);
				EJSON_PARSE_ELEMENT("end parse : 'Number' " << tmpVal << " >> uint64_t=" << m_valueU64);
			}
			return true;
		}
	}
	_pos=_data.size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}

bool ejson::internal::Number::iGenerate(etk::String& _data, size_t _indent) const {
	if (m_typeNumber == ejson::internal::Number::type::tDouble) {
		// special thing to remove .000000 at the end of perfect number ...
		int64_t tmpVal = m_value;
		if (double(tmpVal) == m_value) {
			_data += etk::toString(tmpVal);
		} else {
			_data += etk::toString(m_value);
		}
		return true;
	}
	if (m_typeNumber == ejson::internal::Number::type::tInt) {
		_data += etk::toString(m_valueI64);
		return true;
	}
	_data += etk::toString(m_valueU64);
	return true;
}

void ejson::internal::Number::iMachineGenerate(etk::String& _data) const {
	if (m_typeNumber == ejson::internal::Number::type::tDouble) {
		// special thing to remove .000000 at the end of perfect number ...
		int64_t tmpVal = m_value;
		if (double(tmpVal) == m_value) {
			_data += etk::toString(tmpVal);
		} else {
			_data += etk::toString(m_value);
		}
		return;
	}
	if (m_typeNumber == ejson::internal::Number::type::tInt) {
		_data += etk::toString(m_valueI64);
		return;
	}
	_data += etk::toString(m_valueU64);
	return;
}


bool ejson::internal::Number::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == null) {
		EJSON_ERROR("Request transfer on an null pointer");
		return false;
	}
	if (_obj->getType() != ejson::valueType::Number) {
		EJSON_ERROR("Request transfer on an element that is not an Number");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Number> other = ememory::staticPointerCast<ejson::internal::Number>(_obj);
	// remove destination elements
	other->m_typeNumber = m_typeNumber;
	m_typeNumber = ejson::internal::Number::type::tUint;
	m_valueU64 = 0;
	switch (m_typeNumber) {
		case ejson::internal::Number::type::tDouble:
			other->m_value = m_value;
			break;
		case ejson::internal::Number::type::tInt:
			other->m_valueI64 = m_valueI64;
			break;
		case ejson::internal::Number::type::tUint:
			other->m_valueU64 = m_valueU64;
			break;
	}
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Number::clone() const {
	ememory::SharedPtr<ejson::internal::Number> output;
	switch (m_typeNumber) {
		case ejson::internal::Number::type::tDouble:
			output = ejson::internal::Number::create(m_value);
			break;
		case ejson::internal::Number::type::tInt:
			output = ejson::internal::Number::create(m_valueI64);
			break;
		case ejson::internal::Number::type::tUint:
			output = ejson::internal::Number::create(m_valueU64);
			break;
	}
	if (output == null) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}

void ejson::internal::Number::set(double _value) {
	m_typeNumber = ejson::internal::Number::type::tDouble;
	m_value = _value;
}

void ejson::internal::Number::set(uint64_t _value) {
	m_typeNumber = ejson::internal::Number::type::tUint;
	m_valueU64 = _value;
}

void ejson::internal::Number::set(int64_t _value) {
	m_typeNumber = ejson::internal::Number::type::tInt;
	m_valueI64 = _value;
}

double ejson::internal::Number::get() const {
	switch (m_typeNumber) {
		case ejson::internal::Number::type::tDouble:
			return m_value;
		case ejson::internal::Number::type::tInt:
			return double(m_valueI64);
		case ejson::internal::Number::type::tUint:
			return double(m_valueU64);
	}
	return 0.0;
}

uint64_t ejson::internal::Number::getU64() const {
	switch (m_typeNumber) {
		case ejson::internal::Number::type::tDouble:
			return uint64_t(m_value);
		case ejson::internal::Number::type::tInt:
			return uint64_t(m_valueI64);
		case ejson::internal::Number::type::tUint:
			return m_valueU64;
	}
	return 0;
}

int64_t ejson::internal::Number::getI64() const {
	switch (m_typeNumber) {
		case ejson::internal::Number::type::tDouble:
			return int64_t(m_value);
		case ejson::internal::Number::type::tInt:
			return m_valueI64;
		case ejson::internal::Number::type::tUint:
			return int64_t(m_valueU64);
	}
	return 0;
}
