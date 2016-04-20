/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
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
	if (m_data->isNumber() == false) {
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

double ejson::Number::get() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not parse (nullptr) ...");
		return 0.0;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->get();
}

double ejson::Number::get(double _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not parse (nullptr) ...");
		return _errorValue;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->get();
}

int32_t ejson::Number::getInt32() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getInt32 (nullptr) ...");
		return 0;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->getInt32();
}

int64_t ejson::Number::getInt64() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getInt64 (nullptr) ...");
		return 0;
	}
	return static_cast<ejson::internal::Number*>(m_data.get())->getInt64();
}

