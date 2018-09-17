/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Document.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Document.hpp>
#include <etk/path/fileSystem.hpp>
#include <etk/uri/uri.hpp>

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

bool ejson::Document::load(const etk::Path& _path) {
	if (m_data == null) {
		EJSON_DEBUG("Can not load (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->load(_path);
}

bool ejson::Document::load(const etk::Uri& _uri) {
	if (m_data == null) {
		EJSON_DEBUG("Can not load (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->load(_uri);
}

bool ejson::Document::store(const etk::Path& _path) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->store(_path);
}

bool ejson::Document::store(const etk::Uri& _uri) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Document*>(m_data.get())->store(_uri);
}

bool ejson::Document::storeSafe(const etk::Path& _path) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	bool done = static_cast<ejson::internal::Document*>(m_data.get())->store(_path+".tmp");
	if (done == false) {
		return false;
	}
	return etk::path::move(_path+".tmp", _path);
}

bool ejson::Document::storeSafe(const etk::Uri& _uri) {
	if (m_data == null) {
		EJSON_DEBUG("Can not store (null) ...");
		return false;
	}
	if (etk::uri::canMove(_uri) == false) {
		return static_cast<ejson::internal::Document*>(m_data.get())->store(_uri);
	}
	etk::Uri uriTmp = _uri;
	uriTmp.setPath(uriTmp.getPath() + ".tmp");
	bool done = static_cast<ejson::internal::Document*>(m_data.get())->store(uriTmp);
	if (done == false) {
		return false;
	}
	return etk::uri::move(uriTmp, _uri);
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
