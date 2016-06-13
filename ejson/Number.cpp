/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/Number.h>
#include <ejson/debug.h>
#include <ejson/internal/Number.h>


ejson::Number::Number(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->getType() != ejson::valueType::number) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
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
	if (m_data == nullptr) {
		EJSON_ERROR("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

void ejson::Number::set(uint64_t _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

void ejson::Number::set(int64_t _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Number*>(m_data.get())->set(_value);
}

double ejson::Number::get(double _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return _errorValue;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->get();
}

uint64_t ejson::Number::getU64(uint64_t _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return _errorValue;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->getU64();
}

int64_t ejson::Number::getI64(int64_t _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return _errorValue;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->getI64();
}

ejson::internal::Number::type ejson::Number::getType() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return ejson::internal::Number::type::tDouble;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->getType();
}


