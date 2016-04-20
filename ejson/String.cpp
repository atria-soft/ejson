/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/String.h>
#include <ejson/debug.h>
#include <ejson/internal/String.h>

ejson::String::String(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->isString() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

ejson::String::String(const ejson::String& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::String::String(const std::string& _value) :
  ejson::Value() {
	m_data = ejson::internal::String::create(_value);
}

ejson::String& ejson::String::operator= (const ejson::String& _obj) {
	m_data = _obj.m_data;
	return *this;
}

void ejson::String::set(const std::string& _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::String*>(m_data.get())->set(_value);
}

const std::string& ejson::String::get() const {
	if (m_data == nullptr) {
		static const std::string errorValue = "";
		EJSON_ERROR("Can not get (nullptr) ...");
		return errorValue;
	}
	return static_cast<ejson::internal::String*>(m_data.get())->get();
}
