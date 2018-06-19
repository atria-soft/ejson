/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/Value.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Value.hpp>
#include <ejson/Document.hpp>

ejson::Value ejson::empty() {
	return ejson::Value(ememory::SharedPtr<ejson::internal::Value>(null));
}



etk::Stream& ejson::operator <<(etk::Stream& _os, const ejson::Value& _obj) {
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
	if (m_data == null) {
		EJSON_DEBUG("Can not get type ...");
		return ejson::valueType::Unknow;
	}
	return m_data->getType();
}

bool ejson::Value::exist() const {
	if (m_data == null) {
		return false;
	}
	return true;
}

etk::String ejson::Value::generateHumanString() const {
	etk::String out;
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return out;
	}
	static_cast<const ejson::internal::Value*>(m_data.get())->iGenerate(out, 0);
	return out;
}

etk::String ejson::Value::generateMachineString() const {
	etk::String out;
	if (m_data == null) {
		EJSON_DEBUG("Can not remove (null) ...");
		return out;
	}
	static_cast<const ejson::internal::Value*>(m_data.get())->iMachineGenerate(out);
	return out;
}

/*
ejson::FilePos ejson::Value::getPos() const {
	if (m_data == null) {
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
  m_data(null) {
	
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
	if (m_data == null) {
		EJSON_DEBUG("Can not Display (null) ...");
		return;
	}
	return m_data->display();
}


bool ejson::Value::isDocument() const {
	if (m_data == null) {
		return false;
	}
	enum ejson::valueType type = m_data->getType();
	return type == ejson::valueType::Document;
}

bool ejson::Value::isArray() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::Array;
}

bool ejson::Value::isObject() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::Object;
}

bool ejson::Value::isString() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::String;
}

bool ejson::Value::isNumber() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::Number;
}

bool ejson::Value::isBoolean() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::Boolean;
}

bool ejson::Value::isNull() const {
	if (m_data == null) {
		return false;
	}
	return m_data->getType() == ejson::valueType::Null;
}


void ejson::Value::clear() {
	if (m_data == null) {
		EJSON_DEBUG("Can not Clear (null) ...");
		return;
	}
	return m_data->clear();
}

bool ejson::Value::transfertIn(ejson::Value& _obj) {
	if (m_data == null) {
		EJSON_DEBUG("Can not transfert In (null) ...");
		return false;
	}
	return m_data->transfertIn(_obj.m_data);
}

ejson::Value ejson::Value::clone() const {
	if (m_data == null) {
		EJSON_DEBUG("Can not transfert In (null) ...");
		return ejson::Value(m_data);
	}
	return ejson::Value(m_data->clone());
}

