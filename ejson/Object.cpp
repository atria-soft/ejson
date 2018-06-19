/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Object.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Object.hpp>


ejson::Object::Object(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == null) {
		return;
	}
	if (    m_data->getType() != ejson::valueType::object
	     && m_data->getType() != ejson::valueType::document) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
	
}

ejson::Object::Object(const ejson::Object& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Object::Object() :
  ejson::Value() {
	m_data = ejson::internal::Object::create();
}

ejson::Object::Object(const etk::String& _data) :
  ejson::Value() {
	m_data = ejson::internal::Object::create(_data);
}

ejson::Object& ejson::Object::operator= (const ejson::Object& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool ejson::Object::valueExist(const etk::String& _name) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not exist (null) ...");
		return false;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->exist(_name);
}

ejson::Value ejson::Object::operator[] (const etk::String& _name) {
	if (m_data == null) {
		EJSON_DEBUG("Can not operator[] (null) ...");
		return ejson::Value(null);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_name));
}

const ejson::Value ejson::Object::operator[] (const etk::String& _name) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not operator[] (null) ...");
		return ejson::Value(null);
	}
	return ejson::Value(static_cast<const ejson::internal::Object*>(m_data.get())->get(_name));
}

etk::Vector<etk::String> ejson::Object::getKeys() const {
	if (m_data == null) {
		EJSON_DEBUG("Can not getKeys (null) ...");
		return etk::Vector<etk::String>();
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getKeys();
}

size_t ejson::Object::size() const {
	if (m_data == null) {
		EJSON_DEBUG("Can not size (null) ...");
		return 0;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->size();
}

ejson::Value ejson::Object::operator[] (size_t _id) {
	if (m_data == null) {
		EJSON_DEBUG("Can not operator[] (null) ...");
		return ejson::Value(null);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_id));
}

const ejson::Value ejson::Object::operator[] (size_t _id) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not operator[] (null) ...");
		return ejson::Value(null);
	}
	return ejson::Value(static_cast<const ejson::internal::Object*>(m_data.get())->get(_id));
}

etk::String ejson::Object::getKey(size_t _id) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not getKey (null) ...");
		return "";
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getKey(_id);
}

bool ejson::Object::add(const etk::String& _name, const ejson::Value& _value) {
	if (m_data == null) {
		EJSON_DEBUG("Can not add (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->add(_name, _value.m_data);
}

void ejson::Object::remove(const etk::String& _name) {
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return;
	}
	static_cast<ejson::internal::Object*>(m_data.get())->remove(_name);
}

void ejson::Object::remove(size_t _id) {
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return;
	}
	static_cast<ejson::internal::Object*>(m_data.get())->remove(_id);
}

ejson::Object::iterator ejson::Object::remove(const ejson::Object::iterator& _it) {
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return _it;
	}
	static_cast<ejson::internal::Object*>(m_data.get())->remove(_it.getId());
	return ejson::Object::iterator(*this, _it.getId());
}


ejson::Object::iterator ejson::Object::begin() {
	return ejson::Object::iterator(*this, 0);
}

ejson::Object::iterator ejson::Object::end() {
	return ejson::Object::iterator(*this, size());
}

const ejson::Object::iterator ejson::Object::begin() const {
	return ejson::Object::iterator(*this, 0);
}

const ejson::Object::iterator ejson::Object::end() const {
	return ejson::Object::iterator(*this, size());
}

#include <ejson/details/iterator.hxx>

template class ejson::iterator<ejson::Object>;
namespace ejson {
	template<>
	etk::String iterator<ejson::Object>::getKey() const noexcept {
		return m_data.getKey(m_id);
	}
}

