/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/String.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/String.hpp>

ejson::String::String(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->getType() != ejson::valueType::string) {
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
		EJSON_DEBUG("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::String*>(m_data.get())->set(_value);
}

std::string ejson::String::get(const std::string& _errorValue) const {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not get (nullptr) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::String*>(m_data.get())->get();
}
