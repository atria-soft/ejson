/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/Document.h>
#include <ejson/debug.h>
#include <ejson/internal/Document.h>
#include <etk/os/FSNode.h>

ejson::Document::Document(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Object(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->getType() != ejson::valueType::document) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
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

bool ejson::Document::parse(const std::string& _data) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not parse (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->parse(_data);
}

bool ejson::Document::generate(std::string& _data) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not generate (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->generate(_data);
}

bool ejson::Document::load(const std::string& _file) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not load (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->load(_file);
}

bool ejson::Document::store(const std::string& _file) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not store (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->store(_file);
}

bool ejson::Document::storeSafe(const std::string& _file) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not store (nullptr) ...");
		return false;
	}
	bool done = static_cast<ejson::internal::Document*>(m_data.get())->store(_file+".tmp");
	if (done == false) {
		return false;
	}
	return etk::FSNodeMove(_file+".tmp", _file);
}

void ejson::Document::setDisplayError(bool _value){
	if (m_data == nullptr) {
		EJSON_ERROR("Can not setDisplayError (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Document*>(m_data.get())->setDisplayError(_value);
}

bool ejson::Document::getDisplayError() {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getDisplayError (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->getDisplayError();
}

void ejson::Document::displayError() {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not displayError (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Document*>(m_data.get())->displayError();
}
