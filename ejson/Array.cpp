/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#include <ejson/Array.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Array.hpp>
#include <ejson/Boolean.hpp>
#include <ejson/String.hpp>
#include <ejson/Null.hpp>
#include <ejson/Number.hpp>

ejson::Array::Array(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == null) {
		return;
	}
	if (m_data->getType() != ejson::valueType::Array) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

ejson::Array::Array(const ejson::Array& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Array::Array() :
  ejson::Value() {
	m_data = ejson::internal::Array::create();
}

ejson::Array& ejson::Array::operator= (const ejson::Array& _obj) {
	m_data = _obj.m_data;
	return *this;
}

size_t ejson::Array::size() const {
	if (m_data == null) {
		EJSON_DEBUG("Can not size (null) ...");
		return 0;
	}
	return static_cast<const ejson::internal::Array*>(m_data.get())->size();
}

ejson::Value ejson::Array::operator[] (size_t _id) {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return ejson::Value(null);
	}
	return ejson::Value(static_cast<ejson::internal::Array*>(m_data.get())->get(_id));
}

const ejson::Value ejson::Array::operator[] (size_t _id) const {
	if (m_data == null) {
		EJSON_DEBUG("Can not get (null) ...");
		return ejson::Value(null);;
	}
	return ejson::Value(static_cast<const ejson::internal::Array*>(m_data.get())->get(_id));
}

bool ejson::Array::add(const ejson::Value& _element) {
	if (m_data == null) {
		EJSON_DEBUG("Can not add (null) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->add(_element.m_data);
}

void ejson::Array::remove(size_t _id) {
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return;
	}
	static_cast<ejson::internal::Array*>(m_data.get())->remove(_id);
}

ejson::Array::iterator ejson::Array::remove(const ejson::Array::iterator& _it) {
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return _it;
	}
	static_cast<ejson::internal::Array*>(m_data.get())->remove(_it.getId());
	return ejson::Array::iterator(*this, _it.getId());
}


ejson::Array::iterator ejson::Array::begin() {
	return ejson::Array::iterator(*this, 0);
}

ejson::Array::iterator ejson::Array::end() {
	return ejson::Array::iterator(*this, size());
}

const ejson::Array::iterator ejson::Array::begin() const {
	return ejson::Array::iterator(*this, 0);
}

const ejson::Array::iterator ejson::Array::end() const {
	return ejson::Array::iterator(*this, size());
}


#include <ejson/details/iterator.hxx>

template class ejson::iterator<ejson::Array>;
// Not implemented ==> force link error ...
/*
template<>
etk::String ejson::iterator<ejson::Array>::getKey() const noexcept {
	return m_data.getKey(m_id);
}
*/