/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/Boolean.h>
#include <ejson/debug.h>
#include <ejson/internal/Boolean.h>


ejson::Boolean::Boolean(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->getType() != ejson::valueType::boolean) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

ejson::Boolean::Boolean(const ejson::Boolean& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Boolean::Boolean(bool _value) :
  ejson::Value() {
	m_data = ejson::internal::Boolean::create(_value);
}

ejson::Boolean& ejson::Boolean::operator= (const ejson::Boolean& _obj) {
	m_data = _obj.m_data;
	return *this;
}

void ejson::Boolean::set(bool _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not set (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Boolean*>(m_data.get())->set(_value);
}

bool ejson::Boolean::get(bool _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return _errorValue;
	}
	return static_cast<ejson::internal::Boolean*>(m_data.get())->get();
}

