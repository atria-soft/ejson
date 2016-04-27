/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/Object.h>
#include <ejson/debug.h>
#include <ejson/internal/Object.h>


ejson::Object::Object(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->getType() != ejson::valueType::null) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
	
}

ejson::Object::Object(const ejson::Object& _obj) :
  ejson::Value(_obj.m_data) {
	
}

ejson::Object::Object() :
  ejson::Value() {
	m_data = ejson::internal::Object::create();
}

ejson::Object::Object(const std::string& _data) :
  ejson::Value() {
	m_data = ejson::internal::Object::create(_data);
}

ejson::Object& ejson::Object::operator= (const ejson::Object& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool ejson::Object::valueExist(const std::string& _name) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not exist (nullptr) ...");
		return false;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->exist(_name);
}

ejson::Value ejson::Object::operator[] (const std::string& _name) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not operator[] (nullptr) ...");
		return ejson::Value(nullptr);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_name));
}

const ejson::Value ejson::Object::operator[] (const std::string& _name) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not operator[] (nullptr) ...");
		return ejson::Value(nullptr);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_name));
}

std::vector<std::string> ejson::Object::getKeys() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getKeys (nullptr) ...");
		return std::vector<std::string>();
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->getKeys();
}

size_t ejson::Object::size() const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not size (nullptr) ...");
		return 0;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->size();
}

ejson::Value ejson::Object::operator[] (size_t _id) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not operator[] (nullptr) ...");
		return ejson::Value(nullptr);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_id));
}

const ejson::Value ejson::Object::operator[] (size_t _id) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not operator[] (nullptr) ...");
		return ejson::Value(nullptr);
	}
	return ejson::Value(static_cast<ejson::internal::Object*>(m_data.get())->get(_id));
}

std::string ejson::Object::getKey(size_t _id) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getKey (nullptr) ...");
		return "";
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->getKey(_id);
}

std::string ejson::Object::getStringValue(const std::string& _name, const std::string& _errorValue) const {
	return (*this)[_name].toString().get(_errorValue);
}

bool ejson::Object::getBooleanValue(const std::string& _name, bool _errorValue) const {
	return (*this)[_name].toBoolean().get(_errorValue);
}

double ejson::Object::getNumberValue(const std::string& _name, double _errorValue) const {
	return (*this)[_name].toNumber().get(_errorValue);
}

bool ejson::Object::add(const std::string& _name, const ejson::Value& _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not add (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->add(_name, _value.m_data);
}

bool ejson::Object::addString(const std::string& _name, const std::string& _value) {
	return add(_name, ejson::String(_value));
}

bool ejson::Object::addNull(const std::string& _name) {
	return add(_name, ejson::Null());
}

bool ejson::Object::addBoolean(const std::string& _name, bool _value) {
	return add(_name, ejson::Boolean(_value));
}

bool ejson::Object::addNumber(const std::string& _name, double _value) {
	return add(_name, ejson::Number(_value));
}

void ejson::Object::remove(const std::string& _name) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not remove (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Object*>(m_data.get())->remove(_name);
}

void ejson::Object::remove(size_t _id) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not remove (nullptr) ...");
		return;
	}
	static_cast<ejson::internal::Object*>(m_data.get())->remove(_id);
}

ejson::Object::iterator ejson::Object::remove(const ejson::Object::iterator& _it) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not remove (nullptr) ...");
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

template<>
std::string ejson::iterator<ejson::Object>::getKey() {
	return m_data.getKey(m_id);
}

