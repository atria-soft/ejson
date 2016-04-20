/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/Array.h>
#include <ejson/debug.h>
#include <ejson/internal/Array.h>

ejson::Array::Array(ememory::SharedPtr<ejson::internal::Value> _internalValue) :
  ejson::Value(_internalValue) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->isArray() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
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
	if (m_data == nullptr) {
		EJSON_ERROR("Can not size (nullptr) ...");
		return 0;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->size();
}

ejson::Value ejson::Array::operator[] (size_t _id) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return ejson::Value(nullptr);
	}
	return ejson::Value(static_cast<ejson::internal::Array*>(m_data.get())->get(_id));
}

const ejson::Value ejson::Array::operator[] (size_t _id) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not get (nullptr) ...");
		return ejson::Value(nullptr);;
	}
	return ejson::Value(static_cast<ejson::internal::Array*>(m_data.get())->get(_id));
}

std::string ejson::Array::getStringValue(size_t _id) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not parse (nullptr) ...");
		return "";
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->getStringValue(_id);
}

const std::string& ejson::Array::getStringValue(size_t _id) const {
	if (m_data == nullptr) {
		static const std::string errorValue = "";
		EJSON_ERROR("Can not getStringValue (nullptr) ...");
		return errorValue;
	}
	return static_cast<const ejson::internal::Array*>(m_data.get())->getStringValue(_id);
}

std::string ejson::Array::getStringValue(size_t _id, const std::string& _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getStringValue (nullptr) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Array*>(m_data.get())->getStringValue(_id, _errorValue);
}

double ejson::Array::getNumberValue(size_t _id, double _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getNumberValue (nullptr) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Array*>(m_data.get())->getNumberValue(_id, _errorValue);
}

bool ejson::Array::getBooleanValue(size_t _id, bool _errorValue) const {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not getBooleanValue (nullptr) ...");
		return _errorValue;
	}
	return static_cast<const ejson::internal::Array*>(m_data.get())->getBooleanValue(_id, _errorValue);
}

bool ejson::Array::add(const ejson::Value& _element) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not add (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->add(_element.m_data);
}

bool ejson::Array::addString(const std::string& _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addString (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->addString(_value);
}

bool ejson::Array::addNull() {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addNull (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->addNull();
}

bool ejson::Array::addBoolean(bool _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addBoolean (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->addBoolean(_value);
}

bool ejson::Array::addNumber(double _value) {
	if (m_data == nullptr) {
		EJSON_ERROR("Can not addNumber (nullptr) ...");
		return false;
	}
	return static_cast<ejson::internal::Array*>(m_data.get())->addNumber(_value);
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

