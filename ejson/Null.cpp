/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Null.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Null.hpp>

ejson::Null::Null(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == null) {
		return;
	}
	if (m_data->getType() != ejson::valueType::Null) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

ejson::Null::Null(const ejson::Null& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Null::Null() :
  ejson::Value() {
	m_data = ejson::internal::Null::create();
}

ejson::Null& ejson::Null::operator= (const ejson::Null& _obj) {
	m_data = _obj.m_data;
	return *this;
}

