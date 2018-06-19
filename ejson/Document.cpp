/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Document.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Document.hpp>
#include <etk/os/FSNode.hpp>

ejson::Document::Document(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Object(_internalValue) {
	if (m_data == null) {
		return;
	}
	if (m_data->getType() != ejson::valueType::Document) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

ejson::Document::Document(const ejson::Document& _obj) :
  ejson::Object(_obj.m_data) {
	
}

ejson::Document::Document() :
  ejson::Object() {
	m_data = ejson::internal::Document::create();
}

ejson::Document& ejson::Document::operator= (const ejson::Document& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool ejson::Document::parse(const etk::String& _data) {
	if (m_data == null) {
		EJSON_DEBUG("Can not parse (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->parse(_data);
}

bool ejson::Document::generate(etk::String& _data) {
	if (m_data == null) {
		EJSON_DEBUG("Can not generate (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->generate(_data);
}

bool ejson::Document::load(const etk::String& _file) {
	if (m_data == null) {
		EJSON_DEBUG("Can not load (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->load(_file);
}

bool ejson::Document::store(const etk::String& _file) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->store(_file);
}

bool ejson::Document::storeSafe(const etk::String& _file) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	bool done = static_cast<ejson::internal::Document*>(m_data.get())->store(_file+".tmp");
	if (done == false) {
		return false;
	}
	return etk::FSNodeMove(_file+".tmp", _file);
}

void ejson::Document::setDisplayError(bool _value){
	if (m_data == null) {
		EJSON_DEBUG("Can not setDisplayError (null) ...");
		return;
	}
	static_cast<ejson::internal::Document*>(m_data.get())->setDisplayError(_value);
}

bool ejson::Document::getDisplayError() {
	if (m_data == null) {
		EJSON_DEBUG("Can not getDisplayError (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->getDisplayError();
}

void ejson::Document::displayError() {
	if (m_data == null) {
		EJSON_DEBUG("Can not displayError (null) ...");
		return;
	}
	static_cast<ejson::internal::Document*>(m_data.get())->displayError();
}
