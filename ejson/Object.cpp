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
	if (m_data->isObject() == false) {
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

const std::string& ejson::Object::getStringValue(const std::string& _name) const {
	if (m_data == nullptr) {
		static const std::string errorString = "";
		EJSON_ERROR("Can not getStringValue (nullptr) ...");
		return errorString;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getStringValue(_name);
}

std::string ejson::Object::getStringValue(const std::string& _name, const std::string& _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getStringValue (nullptr) ...");
		return "";
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getStringValue(_name, _errorValue);
}

bool ejson::Object::getBooleanValue(const std::string& _name, bool _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getBooleanValue (nullptr) ...");
		return false;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getBooleanValue(_name, _errorValue);
}

double ejson::Object::getNumberValue(const std::string& _name, double _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getNumberValue (nullptr) ...");
		return 0.0;
	}
	return static_cast<const ejson::internal::Object*>(m_data.get())->getNumberValue(_name, _errorValue);
}

bool ejson::Object::add(const std::string& _name, const ejson::Value& _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not add (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->add(_name, _value.m_data);
}

bool ejson::Object::addString(const std::string& _name, const std::string& _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addString (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->addString(_name, _value);
}

bool ejson::Object::addNull(const std::string& _name) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addNull (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->addNull(_name);
}

bool ejson::Object::addBoolean(const std::string& _name, bool _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addBoolean (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->addBoolean(_name, _value);
}

bool ejson::Object::addNumber(const std::string& _name, double _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addNumber (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Object*>(m_data.get())->addNumber(_name, _value);
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

