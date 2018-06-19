/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Number.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Number.hpp>


ejson::Number::Number(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == null) {
		return;
	}
	if (m_data->getType() != ejson::valueType::number) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

ejson::Number::Number(const ejson::Number& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Number::Number(double _value) :
  ejson::Value() {
	m_data = ejson::internal::Number::create(_value);
}

ejson::Number& ejson::Number::operator= (const ejson::Number& _obj) {
	m_data = _obj.m_data;
	return *this;
}

void ejson::Number::set(double _value) {
	if (m_data == null) {
		EJSON_DEBUG("Can not set (null) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

void ejson::Number::set(uint64_t _value) {
	if (m_data == null) {
		EJSON_DEBUG("Can not set (null) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

void ejson::Number::set(int64_t _value) {
	if (m_data == null) {
		EJSON_DEBUG("Can not set (null) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

double ejson::Number::get(double _errorValue) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Number*>(m_data.get())->get();
}

uint64_t ejson::Number::getU64(uint64_t _errorValue) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Number*>(m_data.get())->getU64();
}

int64_t ejson::Number::getI64(int64_t _errorValue) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Number*>(m_data.get())->getI64();
}

ejson::internal::Number::type ejson::Number::getType() const {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return ejson::internal::Number::type::tDouble;
	}
	return static_cast<const ejson::internal::Number*>(m_data.get())->getType();
}


