/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/Value.h>
#include <ejson/debug.h>
#include <ejson/internal/Value.h>
#include <ejson/Document.h>

ejson::Value ejson::empty() {
	return ejson::Value(ememory::SharedPtr<ejson::internal::Value>(nullptr));
}



std::ostream& ejson::operator <<(std::ostream& _os, const ejson::Value& _obj) {
	_os << "{";
	_os << "Value JSON: " << _obj.getType();
	/*
	if (_obj.isObject() == true) {
		_os << " <" << _obj.getValue() << ">";
	};
	*/
	_os << "}";
	return _os;
}

enum ejson::valueType ejson::Value::getType() const {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not get type ...");
		return ejson::valueType::unknow;
	}
	return m_data->getType();
}

bool ejson::Value::exist() const {
	if (m_data == nullptr) {
		return false;
	}
	return true;
}

std::string ejson::Value::generateHumanString() const {
	std::string out;
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not remove (nullptr) ...");
		return out;
	}
	static_cast<const ejson::internal::Value*>(m_data.get())->iGenerate(out, 0);
	return out;
}

std::string ejson::Value::generateMachineString() const {
	std::string out;
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not remove (nullptr) ...");
		return out;
	}
	static_cast<const ejson::internal::Value*>(m_data.get())->iMachineGenerate(out);
	return out;
}

/*
ejson::FilePos ejson::Value::getPos() const {
	if (m_data == nullptr) {
		return ejson::FilePos(0,0);
	}
	return m_data->getPos();
}
*/

ejson::Value::Value(const ememory::SharedPtr<ejson::internal::Value>& _internalValue) :
  m_data(_internalValue) {
	// nothing to DO ...
}

ejson::Value::Value() :
  m_data(nullptr) {
	
}

ejson::Document ejson::Value::toDocument() {
	return ejson::Document(m_data);
}
const ejson::Document ejson::Value::toDocument() const {
	return ejson::Document(m_data);
}

ejson::Array ejson::Value::toArray() {
	return ejson::Array(m_data);
}
const ejson::Array ejson::Value::toArray() const{
	return ejson::Array(m_data);
}

ejson::Object ejson::Value::toObject() {
	return ejson::Object(m_data);
}
const ejson::Object ejson::Value::toObject() const{
	return ejson::Object(m_data);
}

ejson::String ejson::Value::toString() {
	return ejson::String(m_data);
}
const ejson::String ejson::Value::toString() const{
	return ejson::String(m_data);
}

ejson::Number ejson::Value::toNumber() {
	return ejson::Number(m_data);
}
const ejson::Number ejson::Value::toNumber() const{
	return ejson::Number(m_data);
}

ejson::Boolean ejson::Value::toBoolean() {
	return ejson::Boolean(m_data);
}
const ejson::Boolean ejson::Value::toBoolean() const{
	return ejson::Boolean(m_data);
}

ejson::Null ejson::Value::toNull() {
	return ejson::Null(m_data);
}
const ejson::Null ejson::Value::toNull() const{
	return ejson::Null(m_data);
}

void ejson::Value::display() const {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not Display (nullptr) ...");
		return;
	}
	return m_data->display();
}


bool ejson::Value::isDocument() const {
	if (m_data == nullptr) {
		return false;
	}
	enum ejson::valueType type = m_data->getType();
	return type == ejson::valueType::document;
}

bool ejson::Value::isArray() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::array;
}

bool ejson::Value::isObject() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::object;
}

bool ejson::Value::isString() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::string;
}

bool ejson::Value::isNumber() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::number;
}

bool ejson::Value::isBoolean() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::boolean;
}

bool ejson::Value::isNull() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->getType() == ejson::valueType::null;
}


void ejson::Value::clear() {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not Clear (nullptr) ...");
		return;
	}
	return m_data->clear();
}

bool ejson::Value::transfertIn(ejson::Value& _obj) {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not transfert In (nullptr) ...");
		return false;
	}
	return m_data->transfertIn(_obj.m_data);
}

ejson::Value ejson::Value::clone() const {
	if (m_data == nullptr) {
		EJSON_DEBUG("Can not transfert In (nullptr) ...");
		return ejson::Value(m_data);
	}
	return ejson::Value(m_data->clone());
}

